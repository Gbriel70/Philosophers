/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcosta-m <gcosta-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:10:14 by gcosta-m          #+#    #+#             */
/*   Updated: 2025/02/17 10:36:24 by gcosta-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	*death_routine(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	sem_wait(data->semaphores->death);
	if (simulation_stopped(data, 0))
		return (NULL);
	simulation_stopped(data, 1);
	kill_all_philos(data);
	sem_post(data->semaphores->full);
	return (NULL);
}

void	*all_full_routine(void *arg)
{
	t_data	*data;
	int		philos_full;

	data = (t_data *)arg;
	philos_full = -1;
	while (++philos_full < data->config->nbr_philos)
	{
		sem_wait(data->semaphores->full);
		if (simulation_stopped(data, 0))
			return (NULL);
	}
	simulation_stopped(data, 1);
	kill_all_philos(data);
	sem_post(data->semaphores->death);
	return (NULL);
}

int	main(int ac, char **av)
{
	t_data		data;
	int			i;
	pthread_t	monitor_death;
	pthread_t	monitor_full;

	if (!valid_arguments(ac, av))
		print_error("Error: Invalid arguments");
	init(ac, av, &data);
	i = -1;
	while (++i < data.config->nbr_philos)
	{
		data.philo_pid[i] = ft_fork(&data);
		if (data.philo_pid[i] == 0)
			philo_routine(&data, i);
	}
	pthread_create(&monitor_death, NULL, &death_routine, (void *)&data);
	pthread_create(&monitor_full, NULL, &all_full_routine, (void *)&data);
	pthread_join(monitor_death, NULL);
	pthread_join(monitor_full, NULL);
	wait_finish_philos(&data);
	cleanup(&data);
	return (0);
}
