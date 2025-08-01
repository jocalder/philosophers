/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocalder <jocalder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 16:57:17 by jocalder          #+#    #+#             */
/*   Updated: 2025/07/31 16:57:17 by jocalder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	forks(t_philo *p, pthread_mutex_t **f, pthread_mutex_t **s, bool even)
{
	if (even)
	{
		*f = p->r_fork;
		*s = p->l_fork;
		usleep(1000);
	}
	else
	{
		*f = p->l_fork;
		*s = p->r_fork;
	}
}

void	*philosopher_routine(void *arg)
{
	t_philo			*philo;
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	philo = (t_philo *)arg;
	forks(philo, &first, &second, (philo->id %2 == 0));
	while (1)
	{
		pthread_mutex_lock(&philo->table->check);
		if (philo->table->sim_stop)
		{
			pthread_mutex_unlock(&philo->table->check);
			break ;
		}
		pthread_mutex_unlock(&philo->table->check);
		take_forks(philo, first, second);
		eat_meal(philo);
		release_forks(philo, first, second);
		think_philosopher(philo);
	}
	return (NULL);
}

void	check_philosopher(t_table *table, t_philo *philos)
{
	pthread_mutex_lock(&philos->meal_time);
	if (get_current_time() - philos->last_meal > table->time_to_die)
	{
		pthread_mutex_lock(&table->write);
		print_status(philos, "died", RED);
		pthread_mutex_unlock(&table->write);
		pthread_mutex_lock(&table->check);
		table->sim_stop = true;
		pthread_mutex_unlock(&table->check);
	}
	pthread_mutex_unlock(&philos->meal_time);
}

void	*monitor_philosophers(void *arg)
{
	t_table	*table;
	t_philo	*philos;
	int		i;
	bool	all_ate;

	philos = (t_philo *)arg;
	table = philos->table;
	while (1)
	{
		i = 0;
		all_ate = true;
		while (i < table->nbr_philos)
		{
			check_philosopher(table, &philos[i]);
			pthread_mutex_lock(&philos[i].meal_time);
			if (table->num_meals > 0 && philos[i].times_ate < table->num_meals)
				all_ate = false;
			pthread_mutex_unlock(&philos[i].meal_time);
			i++;
		}
		pthread_mutex_lock(&table->check);
		if (table->sim_stop || (table->num_meals > 0 && all_ate))
		{
			table->sim_stop = true;
			pthread_mutex_unlock(&table->check);
			break ;
		}
		pthread_mutex_unlock(&table->check);
		usleep(1000);
	}
	return (NULL);
}

int	start_simulation(t_table *table, t_philo *philos)
{
	pthread_t	monitor;
	int			i;

	i = 0;
	while (i < table->nbr_philos)
	{
		if (pthread_create(&philos[i].thread, NULL, philosopher_routine,
				&philos[i]) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&philos[i].thread);
		}
		i++;
	}
	if (pthread_create(&monitor, NULL, monitor_philosophers, philos) != 0) ||
		pthread_mutex_destroy(&monitor)
	i = 0;
	while (i < table->nbr_philos)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	pthread_join(monitor, NULL);
	return (0);
}
