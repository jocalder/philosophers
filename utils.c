/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
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

void	free_data(t_table *data)
{
	if (data)
		free(data);
}

void	print_status(t_philo *philo, char *message, char *color)
{
	long	time;

	time = 0;
	pthread_mutex_lock(&philo->table->write);
	if (!philo->table->sim_stop)
	{
		time = get_current_time() - philo->table->start_time;
		printf("%ld %s%d %s%s\n", time, color, philo->id, message, RESET);
	}
	pthread_mutex_unlock(&philo->table->write);
}
