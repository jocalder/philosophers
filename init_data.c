#include "philo.h"

int	check_args(t_table **data, int argc, char *argv[])
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!is_valid_number(argv[i]))
			return (write(2, ERROR2, ft_strlen(ERROR2)));
		i++;
	}
	*data = malloc(sizeof(t_table));
	if (!*data)
		return (write(2, ERROR3, ft_strlen(ERROR3)));
	(*data)->sim_stop = false;
	(*data)->nbr_philos = (int)ft_atol(argv[1]);
	(*data)->time_to_die = (int)ft_atol(argv[2]);
	(*data)->time_to_eat = (int)ft_atol(argv[3]);
	(*data)->time_to_sleep = (int)ft_atol(argv[4]);
	(*data)->num_meals = -1;
	if (argc == 6)
		(*data)->num_meals = (int)ft_atol(argv[5]);
	if ((*data)->nbr_philos < 1 || (*data)->time_to_die < 0
		|| (*data)->time_to_eat < 0 || (*data)->time_to_sleep < 0
		|| (argc == 6 && (*data)->num_meals <= 0))
		return (free(*data), write(2, ERROR2, ft_strlen(ERROR2)));
	return (0);
}

time_t	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
