#ifndef	PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>
# include <limits.h>

# define RED			"\001\033[0;34m\002"
# define BLUE			"\001\033[0;31m\002"
# define WHITE			"\001\033[0m\002"
# define GREEN			"\001\033[0;32m\002"
# define YELLOW 		"\001\033[0;33m\002"

# define ERROR1	"Usage: number_philo, t_die, t_eat, t_sleep, [meals_of_each_philosopher]\n"
# define ERROR2 "Usage: Invalid numbers, please use a integer between 0 and 2147483647.\n"
# define ERROR3	"Cannot be allocated"

typedef struct s_table
{
	unsigned int	nbr_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_meals;
	pthread_mutex_t	write;
	pthread_mutex_t	check;
	bool			sim_stop;
}	t_table;

typedef struct s_philo
{
	pthread_t		thread;
	unsigned int	id;
	unsigned int	times_ate;
	unsigned int	fork_left;
	unsigned int	fork_right;
	time_t			last_meal;
	pthread_mutex_t	meal_time;
	t_table			*table;
}	t_philo;


/*init_data*/
int	check_args(t_table **data, int argc, char *argv[]);
/*Utils*/

bool	is_valid_number(char *str);
int		ft_strlen(char *str);
long	ft_atol(char *str);
void	free_data(t_table *data);

# endif
