/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocalder <jocalder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 16:58:46 by jocalder          #+#    #+#             */
/*   Updated: 2025/07/31 16:58:46 by jocalder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	forks(t_philo *p, pthread_mutex_t **f, pthread_mutex_t **s, bool even)
{
	if (even)
	{
		*f = p->r_fork;
		*s = p->l_fork;
		usleep(100);
	}
	else
	{
		*f = p->l_fork;
		*s = p->r_fork;
	}
}

bool	take_forks(t_philo *philo,
					pthread_mutex_t *first, pthread_mutex_t *second)
{
	pthread_mutex_lock(first);
	if (!is_simulation_running(philo))
	{
		pthread_mutex_unlock(first);
		return (false);
	}
	print_action(philo, "has taken a fork", YELLOW);
	pthread_mutex_lock(second);
	if (!is_simulation_running(philo))
	{
		pthread_mutex_unlock(first);
		pthread_mutex_unlock(second);
		return (false);
	}
	print_action(philo, "has taken a fork", YELLOW);
	if (!is_simulation_running(philo))
	{
		pthread_mutex_unlock(first);
		pthread_mutex_unlock(second);
		return (false);
	}
	return (true);
}

bool	is_eating(t_philo *philo, t_table *table,
					pthread_mutex_t *first, pthread_mutex_t *second)
{
	pthread_mutex_lock(&table->meal_lock);
	philo->last_meal_time = get_current_time();
	if (!is_simulation_running(philo))
	{
		pthread_mutex_unlock(first);
		pthread_mutex_unlock(second);
		pthread_mutex_unlock(&table->meal_lock);
		return (false);
	}
	print_action(philo, "is eating", GREEN);
	philo->times_ate++;
	pthread_mutex_unlock(&table->meal_lock);
	wait_action(table->time_to_eat, philo);
	pthread_mutex_unlock(first);
	pthread_mutex_unlock(second);
	return (true);
}

bool	is_sleeping(t_philo *philo, t_table *table)
{
	if (!is_simulation_running(philo))
		return (false);
	print_action(philo, "is sleeping", MAGENTA);
	wait_action(table->time_to_sleep, philo);
	return (true);
}

void	is_thinking(t_philo *philo)
{
	print_action(philo, "is thinking", BLUE);
}
