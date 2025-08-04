/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocalder <jocalder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 16:58:40 by jocalder          #+#    #+#             */
/*   Updated: 2025/07/31 16:58:40 by jocalder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutex_lock(t_table *table)
{
	if (!table)
		return ;
	pthread_mutex_destroy(&table->meal_lock);
	pthread_mutex_destroy(&table->write);
	pthread_mutex_destroy(&table->check);
}

void	destroy_mutex_info(t_table *table, int i)
{
	if (!table)
		return ;
	destroy_mutex_lock(table);
	if (i <= 0)
		return (free(table->forks));
	while (--i >= 0)
		pthread_mutex_destroy(&table->forks[i]);
	free(table->forks);
}

void	destroy_all_mutex(t_table *table, t_philo *philos, int i)
{
	if (!table && !philos)
		return ;
	while (--i >= 0)
		pthread_join(philos[i].thread, NULL);
	destroy_mutex_info(table, table->nbr_philos);
	exit(EXIT_FAILURE);
}
