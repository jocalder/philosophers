#include "philo.h"

static void	print_values(t_table *data)
{
	if (!data)
	{
		printf(RED "Error: Null data pointer\n" WHITE);
		return;
	}

	printf(GREEN "\n--- Philosophers Data ---\n" WHITE);
	printf(BLUE "Address of struct: %p\n" WHITE, (void *)data);
	printf("Number of philosophers: %u\n", data->nbr_philos);
	printf("Time to die (ms): %d\n", data->time_to_die);
	printf("Time to eat (ms): %d\n", data->time_to_eat);
	printf("Time to sleep (ms): %d\n", data->time_to_sleep);
	
	if (!data->num_meals)
		printf("Optional meals: " YELLOW "Not specified\n" WHITE);
	else
		printf("Optional meals: %d\n", data->num_meals);

	printf("\n" BLUE "Mutex Addresses:\n" WHITE);
	printf("Write mutex: %p\n", (void *)&data->write);
	printf("Check mutex: %p\n", (void *)&data->check);
	
	/*printf("\n" MAGENTA "Simulation status: " WHITE);
	if (data->sim_stop)
		printf(RED "STOPPED\n" WHITE);
	else
		printf(GREEN "RUNNING\n" WHITE);*/
	
	printf("--------------------------------\n\n");
}

int	main(int argc, char **argv)
{
	t_table	*data;
	t_philo	*philos;

	data = NULL;
	philos = NULL;
	if (argc < 5 || argc > 6)
		return (write(2, ERROR1, ft_strlen(ERROR1)));
	if (check_args(&data, argc, argv) != 0)
		return (1);
	if (init_philosophers(data, &philos) != 0)
		return (free_resources(data, philos), 1);
	print_values(data);
	data->start_time = get_current_time();
	start_simulation(data, philos);
	free_resources(data, philos);
	return (0);
}
