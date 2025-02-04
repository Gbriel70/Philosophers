#include "../includes/philo.h"

int main(int ac, char **av)
{
	t_data *data;

	if (!valid_arguments(ac, av))
		return (print_error("Invalid arguments"));
	data = init(ac, av);
	simulate(data);
	return (0);
}