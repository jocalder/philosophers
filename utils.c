#include "philo.h"

bool	is_valid_number(char *str)
{
	size_t	i;

	i = 0;
	if (!str || !*str)
		return (0);
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
		i++;
	}
	return (true);
}

long	ft_atol(char *str)
{
	long 	nbr;
	int		i;

	nbr = 0;
	i = 0;
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = nbr * 10 + (str[i] - '0');
		if (nbr > INT_MAX)
			return (-1);
		i++;
	}
	return (nbr);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	free_data(t_table *data)
{
	if (data)
		free(data);
	printf("data_pointer after be freed: %p\n", data);
}
