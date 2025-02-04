#include "../includes/philo.h"

int main(int ac, char **av)
{
	if (!valid_arguments(ac, av))
		return (print_error("Invalid arguments"));
	init(ac, av);
	return (0);
}