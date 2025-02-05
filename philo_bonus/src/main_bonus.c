#include "../includes/philo_bonus.h"

int main(int ac, char **av)
{
    t_data *data;

    if (!valid_arguments(ac, av))
        print_error("Error: Invalid arguments");
    data = init(ac, av);
    error_exit("kill everything", data, 4);
    return (0);
}