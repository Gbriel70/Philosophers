/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcosta-m <gcosta-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:10:26 by gcosta-m          #+#    #+#             */
/*   Updated: 2025/02/10 17:10:31 by gcosta-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static short	init_config(t_config *config, int ac, char **av);
static short	init_monitor(t_monitor *monitor);
static short	init_semaphores(t_semaphores *semaphores, int nbr_philos);

short			unlink_semaphores(void);
short			set_unlinked_semaphores(t_semaphores *semaphores,
					int nbr_philos);

t_data	*init(int ac, char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		print_error("Error: malloc failed");
	data->config = malloc(sizeof(t_config));
	if (!data->config)
		error_exit("Error: malloc config failed", data, 1);
	else if (init_config(data->config, ac, av) != TRUE)
		error_exit("Error: init_config failed", data, 2);
	data->monitor = malloc(sizeof(t_monitor));
	if (!data->monitor)
		error_exit("Error: malloc monitor failed", data, 2);
	else if (init_monitor(data->monitor) != TRUE)
		error_exit("Error: init_monitor failed", data, 3);
	data->semaphores = malloc(sizeof(t_semaphores));
	if (!data->semaphores)
		error_exit("Error: malloc failed", data, 3);
	else if (init_semaphores(data->semaphores,
			data->config->nbr_philos) != TRUE)
		error_exit("Error: init_semaphores failed", data, 4);
	return (data);
}

static short	init_config(t_config *config, int ac, char **av)
{
	config->nbr_philos = ft_atoi(av[1]);
	config->time_to_die = ft_atoi(av[2]);
	config->time_to_eat = ft_atoi(av[3]);
	config->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		config->times_must_eat = ft_atoi(av[5]);
	else
		config->times_must_eat = -1;
	return (TRUE);
}

static short	init_monitor(t_monitor *monitor)
{
	monitor->sim_stop = FALSE;
	monitor->start_time = get_current_time_ms();
	return (TRUE);
}

static short	init_semaphores(t_semaphores *semaphores, int nbr_philos)
{
	if (unlink_semaphores() != TRUE)
		return (FALSE);
	else if (set_unlinked_semaphores(semaphores, nbr_philos) != TRUE)
		return (FALSE);
	return (TRUE);
}

short	unlink_semaphores(void)
{
	sem_unlink("/forks");
	sem_unlink("/table");
	sem_unlink("/print");
	sem_unlink("/death");
	sem_unlink("/full");
	sem_unlink("/stop");
	sem_unlink("/sem_state");
	return (TRUE);
}

short	set_unlinked_semaphores(t_semaphores *semaphores, int nbr_philos)
{
	semaphores->forks = sem_open("/forks", O_CREAT, 0660, nbr_philos);
	semaphores->table = sem_open("/table", O_CREAT, 0660, 1);
	semaphores->print = sem_open("/print", O_CREAT, 0660, 1);
	semaphores->death = sem_open("/death", O_CREAT, 0660, 1);
	semaphores->full = sem_open("/full", O_CREAT, 0660, 0);
	semaphores->stop = sem_open("/stop", O_CREAT, 0660, 1);
	semaphores->sem_state = sem_open("/sem_state", O_CREAT, 0660, 1);
	if (semaphores->forks == SEM_FAILED || semaphores->table == SEM_FAILED
		|| semaphores->print == SEM_FAILED || semaphores->death == SEM_FAILED
		|| semaphores->full == SEM_FAILED || semaphores->stop == SEM_FAILED
		|| semaphores->sem_state == SEM_FAILED)
		return (FALSE);
	return (TRUE);
}
