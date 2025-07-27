#include "philo.h"

int	init_mutex(t_table *table)
{
	int	i;

	i = 0;
	table->forks = malloc(sizeof(pthread_mutex_t) * table->nbr_philos);
	if (!table->forks)
		return (1);
	while (i < table->nbr_philos)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&table->forks[i]);
			return (free(table->forks), 1);
		}
		i++;
	}
	if (pthread_mutex_init(&table->write, NULL) ||
		pthread_mutex_init(&table->check, NULL))
		return (1);
	return (0);
}

int	init_philosophers(t_table *table, t_philo **philos)
{
	int	i;

	i = 0;
	*philos = malloc(sizeof(t_philo) * table->nbr_philos);
	if (!*philos)
		return (1);
	table->start_time = get_current_time();
	table->sim_stop = false;
	while (i < table->nbr_philos)
	{
		(*philos)[i].id = i + 1;
		(*philos)[i].times_ate = 0;
		(*philos)[i].last_meal = table->start_time;
		(*philos)[i].table = table;
		(*philos)[i].fork_left = i;
		(*philos)[i].fork_right = (i + 1) % table->nbr_philos;
		if (pthread_mutex_init(&(*philos)[i].meal_time, NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&(*philos)[i].meal_time);
			return (free(table->forks), 1);
		}
		i++;
	}
	return (init_mutex(table));
}
