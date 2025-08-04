/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocalder <jocalder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 16:57:37 by jocalder          #+#    #+#             */
/*   Updated: 2025/07/31 16:57:37 by jocalder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_valid_number(char *str)
{
	size_t	i;

	i = 0;
	if (!str || !*str)
		return (0);
	while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == 32))
		i++;
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
	long	nbr;
	int		i;

	nbr = 0;
	i = 0;
	while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == 32))
		i++;
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

void	check_args(int argc, char *argv[])
{
	int	i;

	i = 1;
	if (argc < 5 || argc > 6)
	{
		write(2, ERROR1, ft_strlen(ERROR1));
		exit(EXIT_FAILURE);
	}
	while (i < argc)
	{
		if (!is_valid_number(argv[i]) || ft_atol(argv[i]) > INT_MAX)
			write(2, ERROR2, ft_strlen(ERROR2));
		i++;
	}
}
