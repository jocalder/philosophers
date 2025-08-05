/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocalder <jocalder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 16:57:24 by jocalder          #+#    #+#             */
/*   Updated: 2025/07/31 16:57:24 by jocalder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*single_philo_case(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	print_action(philo, "has taken a fork", YELLOW);
	usleep(philo->table->time_to_die * 1);
	print_action(philo, "died", RED);
	pthread_mutex_unlock(philo->l_fork);
	return (NULL);
}

long long	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000LL) + (time.tv_usec / 1000));
}

void	print_action(t_philo *philo, char *message, char *color)
{
	long long	time;

	time = 0;
	pthread_mutex_lock(&philo->table->write);
	if (!philo->table->death)
	{
		time = get_current_time() - philo->table->start_time;
		printf("%lld %s%d %s%s\n", time, color, philo->id, message, RESET);
	}
	pthread_mutex_unlock(&philo->table->write);
}

void	wait_action(long long duration, t_philo *philo)
{
	long long	start;

	start = get_current_time();
	while ((get_current_time() - start) < duration)
	{
		if (!is_simulation_running(philo))
			break ;
		usleep(100);
	}
}

bool	is_simulation_running(t_philo *philo)
{
	t_table	*table;
	bool	running;

	table = philo->table;
	pthread_mutex_lock(&table->check);
	running = !(table->death || table->all_ate);
	pthread_mutex_unlock(&table->check);
	return (running);
}
