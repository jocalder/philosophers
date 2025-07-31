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

void	take_forks(t_philo *philo, pthread_mutex_t *f, pthread_mutex_t *s)
{
	pthread_mutex_lock(first);
	print_status(philo, "has taken a fork", YELLOW);
	pthread_mutex_lock(second);
	print_status(philo, "has taken a fork", YELLOW);
}

void	eat_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_time);
	philo->last_meal = get_current_time();
	print_status(philo, "is eating", GREEN);
	philo->times_ate++;
	pthread_mutex_unlock(&philo->meal_time);
	usleep(philo->table->time_to_eat * 1000);
}

void	release_forks(t_philo *philo, pthread_mutex_t *f, pthread_mutex_t *s)
{
	pthread_mutex_unlock(first);
	pthread_mutex_unlock(second);
	print_status(philo, "is sleeping", MAGENTA);
	usleep(philo->table->time_to_sleep * 1000);
}

void	think_philosopher(t_philo *philo)
{
	print_status(philo, "is thinking", BLUE);
}
