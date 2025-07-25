#include "philo.h"

int	check_args(t_table **data, int argc, char *argv[])
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (!is_valid_number(argv[i]))
			return (write(2, ERROR2, ft_strlen(ERROR2)));
		i++;
	}
	*data = malloc(sizeof(t_table));
	if (!*data)
		return (write(2, ERROR3, ft_strlen(ERROR3)));
	(*data)->nbr_philos = (unsigned int)ft_atol(argv[1]);
	(*data)->time_to_die = (int)ft_atol(argv[2]);
	(*data)->time_to_eat = (int)ft_atol(argv[3]);
	(*data)->time_to_sleep = (int)ft_atol(argv[4]);
	if (argc == 6)
		(*data)->num_meals = (int)ft_atol(argv[5]);
	if ((*data)->nbr_philos < 1 || (*data)->time_to_die < 0
		|| (*data)->time_to_eat < 0 || (*data)->time_to_sleep < 0
		|| ((*data)->num_meals <= 0 && argc == 6))
		return (write(2, ERROR2, ft_strlen(ERROR2)));
	return (0);
}
