/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocalder <jocalder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 16:58:52 by jocalder          #+#    #+#             */
/*   Updated: 2025/07/31 16:58:52 by jocalder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>
# include <limits.h>
# include <time.h>

# define RESET			"\001\033[0m\002"
# define RED			"\001\033[0;31m\002"
# define GREEN			"\001\033[0;32m\002"
# define YELLOW 		"\001\033[0;33m\002"
# define BLUE			"\001\033[0;34m\002"
# define MAGENTA		"\001\033[35m\002"
# define CYAN			"\001\033[36m\002"
# define WHITE			"\001\033[37m\002"

# define ERROR1	"Usage: number_philo, t_die, t_eat, t_sleep, [meals]\n"
# define ERROR2 "Usage: Use valid integer between 0 and 2147483647.\n"
# define ERROR3	"Cannot be allocated"

typedef struct s_table
{
	int				nbr_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_meals;
	time_t			start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
	pthread_mutex_t	check;
	bool			sim_stop;
}	t_table;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				times_ate;
	time_t			last_meal;
	pthread_mutex_t	meal_time;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	t_table			*table;
}	t_philo;

/*init_data*/
int		check_args(t_table **data, int argc, char *argv[]);
time_t	get_current_time(void);

/*init_philos*/
int		init_mutex(t_table *table);
int		init_philosophers(t_table *table, t_philo **philos);

/*routines*/
void	*philosopher_routine(void *arg);
void	check_philosopher(t_table *table, t_philo *philos);
void	*monitor_philosophers(void *arg);
int		start_simulation(t_table *table, t_philo *philos);
void	forks(t_philo *p, pthread_mutex_t **f, pthread_mutex_t **s, bool even);

/*actions*/
void	take_forks(t_philo *philo, pthread_mutex_t *f, pthread_mutex_t *s);
void	eat_meal(t_philo *philo);
void	release_forks(t_philo *philo, pthread_mutex_t *f, pthread_mutex_t *s);
void	think_philosopher(t_philo *philo);

/*utils*/
bool	is_valid_number(char *str);
int		ft_strlen(char *str);
long	ft_atol(char *str);
void	free_data(t_table *data);
void	print_status(t_philo *philo, char *message, char *color);

/*free_data*/
void	free_philosophers(t_philo *philo, int count);
void	free_table(t_table *table);
void	free_resources(t_table *table, t_philo *philos);

#endif
