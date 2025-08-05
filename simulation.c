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

static void	*philosopher_routine(void *arg)
{
	t_philo			*philo;
	t_table			*table;
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	philo = (t_philo *)arg;
	table = philo->table;
	while (get_current_time() < table->start_time)
		usleep(100);
	forks(philo, &first, &second, (philo->id % 2 == 0));
	if (table->nbr_philos == 1)
		return (single_philo_case(philo));
	while (is_simulation_running(philo))
	{
		if (!take_forks(philo, first, second))
			return (NULL);
		if (!is_eating(philo, table, first, second))
			return (NULL);
		if (!is_sleeping(philo, table))
			return (NULL);
		if (!is_simulation_running(philo))
			return (NULL);
		is_thinking(philo);
	}
	return (NULL);
}

static bool	check_philo_death(t_philo *philo)
{
	long long	now;
	t_table		*table;
	long long	last_meal;

	table = philo->table;
	now = get_current_time();
	pthread_mutex_lock(&table->meal_lock);
	last_meal = philo->last_meal_time;
	pthread_mutex_unlock(&table->meal_lock);
	if ((now - last_meal) > table->time_to_die)
	{
		pthread_mutex_lock(&table->check);
		if (!table->death)
		{
			print_action(philo, "died", RED);
			table->death = true;
			pthread_mutex_unlock(&table->check);
		}
		else
			pthread_mutex_unlock(&table->check);
		return (true);
	}
	return (false);
}

static bool	check_all_ate(t_philo *philo, t_table *table)
{
	int	i;
	int	full;

	i = 0;
	full = 0;
	while (i < table->nbr_philos)
	{
		pthread_mutex_lock(&table->meal_lock);
		if (table->num_meals != -1 && philo[i].times_ate >= table->num_meals)
			full++;
		pthread_mutex_unlock(&table->meal_lock);
		i++;
	}
	if (table->num_meals != -1 && full == table->nbr_philos)
	{
		pthread_mutex_lock(&table->check);
		table->all_ate = true;
		pthread_mutex_unlock(&table->check);
		return (true);
	}
	return (false);
}

static void	*monitor_philosophers(void *arg)
{
	t_table	*table;
	t_philo	*philo;
	int		i;

	philo = (t_philo *)arg;
	table = philo[0].table;
	while (1)
	{
		if (check_all_ate(philo, table))
			return (NULL);
		i = 0;
		while (i < table->nbr_philos)
		{
			if (check_philo_death(&philo[i]))
				return (NULL);
			i++;
		}
		usleep(100);
	}
	return (NULL);
}

void	start_simulation(t_table *table, t_philo *philos)
{
	pthread_t	monitor;
	int			i;

	i = 0;
	(*table).start_time = get_current_time();
	while (i < table->nbr_philos)
	{
		philos[i].last_meal_time = table->start_time;
		if (pthread_create(&philos[i].thread, NULL, philosopher_routine,
				&philos[i]))
			destroy_all_mutex(table, philos, i);
		i++;
	}
	if (pthread_create(&monitor, NULL, monitor_philosophers, philos))
		destroy_all_mutex(table, philos, i);
	i = 0;
	while (i < table->nbr_philos)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	pthread_join(monitor, NULL);
	free(philos);
	destroy_mutex_info(table, i);
	return ;
}
