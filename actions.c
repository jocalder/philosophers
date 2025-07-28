#include "philo.h"

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 != 2)
	{
		pthread_mutex_lock(&philo->table->forks[philo->fork_left]);
		print_status(philo, "has taken a fork", YELLOW);
		pthread_mutex_lock(&philo->table->forks[philo->fork_right]);
		print_status(philo, "has taken a fork", YELLOW);
	}
	else
	{
		pthread_mutex_lock(&philo->table->forks[philo->fork_right]);
		print_status(philo, "has taken a fork", YELLOW);
		pthread_mutex_lock(&philo->table->forks[philo->fork_left]);
		print_status(philo, "has taken a fork", YELLOW);
	}
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

void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->table->forks[philo->fork_left]);
    pthread_mutex_unlock(&philo->table->forks[philo->fork_right]);
	print_status(philo, "is sleeping", MAGENTA);
	usleep(philo->table->time_to_sleep * 1000);
}

void	think_philosopher(t_philo *philo)
{
	print_status(philo, "is thinking", BLUE);
}
