/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocalder <jocalder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 16:57:32 by jocalder          #+#    #+#             */
/*   Updated: 2025/07/31 16:57:32 by jocalder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	data;
	t_philo	*philos;

	check_args(argc, argv);
	init_args(&data, argv);
	init_philosophers(&data, &philos);
	start_simulation(&data, philos);
	return (0);
}
