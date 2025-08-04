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
# define ERROR4 "Error: nbr of philosphers should not exceed 200\n"

# define PHILO_MAX 200

typedef struct s_table
{
	int				nbr_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_meals;
	bool			death;
	bool			all_ate;
	long long		start_time;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write;
	pthread_mutex_t	check;
	pthread_mutex_t	*forks;
}	t_table;

typedef struct s_philo
{
	int				id;
	int				times_ate;
	long long		last_meal_time;
	pthread_t		thread;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	t_table			*table;
}	t_philo;


/*init_philos*/
void		init_args(t_table *data, char **argv);
int			init_philosophers(t_table *table, t_philo **philos);

/*simulation*/
void		start_simulation(t_table *table, t_philo *philos);
void		forks(t_philo *p, pthread_mutex_t **f,
				pthread_mutex_t **s, bool even);

/*actions*/
bool		take_forks(t_philo *philo,
				pthread_mutex_t *first, pthread_mutex_t *second);
bool		is_eating(t_philo *philo, t_table *table,
				pthread_mutex_t *first, pthread_mutex_t *second);
bool		is_sleeping(t_philo *philo, t_table *table);
void		is_thinking(t_philo *philo);

/*parsing*/
bool		is_valid_number(char *str);
long		ft_atol(char *str);
int			ft_strlen(char *str);
void		check_args(int argc, char *argv[]);

/*free_data*/
void		destroy_mutex_lock(t_table *table);
void		destroy_mutex_info(t_table *table, int i);
void		destroy_all_mutex(t_table *table, t_philo *philos, int i);

/*utils*/
long long	get_current_time(void);
void		print_action(t_philo *philo, char *message, char *color);
void		wait_action(long long duration, t_philo *philo);
bool		is_simulation_running(t_philo *philo);
void		*single_philo_case(t_philo *philo);

#endif
