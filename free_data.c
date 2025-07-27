#include "philo.h"

void	free_philosophers(t_philo *philos, int count)
{
	if (!philos)
		return ;
	if (count > 0)
	{
		pthread_mutex_destroy(&philos[count - 1].meal_time);
		free_philosophers(philos, count - 1);
	}
	else
		free(philos);
}

void	free_table(t_table *table)
{
	if (!table)
	return ;
	if (table->forks)
	{
		pthread_mutex_destroy(&table->forks[table->nbr_philos - 1]);
		free(table->forks);
	}
	pthread_mutex_destroy(&table->write);
	pthread_mutex_destroy(&table->check);
	free(table);
}

void	free_resources(t_table *table, t_philo *philos)
{
	if (!table && !philos)
		return ;
	if (table && philos)
		free_philosophers(philos, table->nbr_philos);
	free_table(table);
}
