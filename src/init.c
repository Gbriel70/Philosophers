#include "../includes/philo.h"

int init_data(int ac, char **av, t_data *data)
{
	int	stage;

	data->nbr_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->max_meals = ft_atoi(av[5]);
	else
		data->max_meals = -1;
	data->forks = (pthread_mutex_t *)malloc(data->nbr_philo * sizeof(pthread_mutex_t));
	if (!data->forks)
		return (print_error("Error: malloc failed"), 1);
	if (pthread_mutex_init(data->print_mutex, NULL) != 0)
		return (print_error("Error: mutex init failed"), 1);
	stage = init_mutexes(data);
	if (stage != 0)
	{
		if (stage >= 1)
			destroy_mutexes(data);
		return (1);
	}
	return (0);
}

void init_philo_data(t_philo *philos, t_data *data)
{
	int i;

	i = 0;
	while (i < data->nbr_philo)
	{
		philos[i].id = i + 1;
		philos[i].meals_eaten = 0;
		philos[i].last_meal = 0;
		philos[i].right_fork = &data->forks[i];
		philos[i].left_fork = &data->forks[(i + 1) % data->nbr_philo];
		philos[i].data = data;
		i++;
	}
}

int init_mutexes(t_data *data)
{
	int i;

	i = 0;
	while (i < data->nbr_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&data->forks[i]);
			return (print_error("Error: mutex init failed"), 1);
		}
		i++;
	}
	return (0);
}

void destroy_mutexes(t_data *data)
{
	int i;

	i = 0;
	while (i < data->nbr_philo)
		pthread_mutex_destroy(&data->forks[i++]);
	pthread_mutex_destroy(data->print_mutex);
}