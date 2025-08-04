/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocalder <jocalder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 16:57:28 by jocalder          #+#    #+#             */
/*   Updated: 2025/07/31 16:57:28 by jocalder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_mutex(t_table *table)
{
	int	i;

	if (pthread_mutex_init(&table->meal_lock, NULL))
		return (1);
	if (pthread_mutex_init(&table->write, NULL))
	{
		pthread_mutex_destroy(&table->meal_lock);
		return (1);
	}
	if (pthread_mutex_init(&table->check, NULL))
	{
		pthread_mutex_destroy(&table->meal_lock);
		pthread_mutex_destroy(&table->write);
		return (1);
	}
	table->forks = malloc(sizeof(pthread_mutex_t) * table->nbr_philos);
	if (!table->forks)
		return (destroy_mutex_lock(table), 1);
	i = -1;
	while (--i < table->nbr_philos)
	{
		if (pthread_mutex_init(&table->forks[i], NULL))
			return (destroy_mutex_info(table, i), 1);
	}
	return (0);
}

void	init_args(t_table *data, char **argv)
{
	(*data).nbr_philos = (int)ft_atol(argv[1]);
	if ((*data).nbr_philos > PHILO_MAX)
	{
		write(2, ERROR4, ft_strlen(ERROR4));
		exit(EXIT_FAILURE);
	}
	(*data).time_to_die = (int)ft_atol(argv[2]);
	(*data).time_to_eat = (int)ft_atol(argv[3]);
	(*data).time_to_sleep = (int)ft_atol(argv[4]);
	(*data).num_meals = -1;
	if (argv[5])
		(*data).num_meals = (int)ft_atol(argv[5]);
	(*data).death = false;
	(*data).all_ate = false;
	if (init_mutex(data))
		exit(EXIT_FAILURE);
}

int	init_philosophers(t_table *table, t_philo **philos)
{
	int	i;

	i = 0;
	if (!philos)
	{
		if (table)
			destroy_mutex_info(table, table->nbr_philos);
		exit(EXIT_FAILURE);
	}
	*philos = malloc(sizeof(t_philo) * table->nbr_philos);
	if (!*philos)
	{
		destroy_mutex_info(table, table->nbr_philos);
		exit(EXIT_FAILURE);
	}
	while (i < table->nbr_philos)
	{
		(*philos)[i].id = i + 1;
		(*philos)[i].times_ate = 0;
		(*philos)[i].table = table;
		(*philos)[i].l_fork = &table->forks[i];
		(*philos)[i].r_fork = &table->forks[(i + 1) % table->nbr_philos];
		i++;
	}
	return (0);
}
