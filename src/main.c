#include "../includes/philo.h"

int main(int ac, char **av)
{
	t_data data;
	t_philo *philos;
	int data_init_return;

	(void)philos;

	if (!valid_arguments(ac, av))
		return (print_error("Invalid arguments"));
	data_init_return = init_data(ac, av, &data);
	if (data_init_return != 0)
		return (print_error("Error initializing data"));
	if (data.nbr_philo > 0)
	{
		philos = (t_philo *)malloc(data.nbr_philo * sizeof(t_philo));
		if (philos)
		{
			init_philo_data(philos, &data);
			// run_simulation(philos);
			free(philos);
		}
		else
			return (print_error("Error: malloc failed"), 1);
	}
	destroy_mutexes(&data);
	return (0);
}