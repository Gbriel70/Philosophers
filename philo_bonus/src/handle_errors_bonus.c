/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcosta-m <gcosta-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:10:33 by gcosta-m          #+#    #+#             */
/*   Updated: 2025/02/17 10:45:04 by gcosta-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static void	free_semaphores(t_semaphores *semaphores);

void	error_exit(char *message, t_data *data, int stage)
{
	print_error(message);
	free_data(data, stage);
	exit(EXIT_FAILURE);
}

void	free_data(t_data *data, int stage)
{
	if (!data)
		return ;
	if (stage >= 4)
	{
		if (data->semaphores)
			free_semaphores(data->semaphores);
		if (data->philo_pid)
			free(data->philo_pid);
	}
	if (stage >= 3)
	{
		if (data->monitor)
			free(data->monitor);
	}
	if (stage >= 2)
	{
		if (data->config)
			free(data->config);
	}
	free(data);
}

static void	free_semaphores(t_semaphores *semaphores)
{
	if (!semaphores)
		return ;
	if (semaphores->forks)
		sem_close(semaphores->forks);
	if (semaphores->table)
		sem_close(semaphores->table);
	if (semaphores->print)
		sem_close(semaphores->print);
	if (semaphores->death)
		sem_close(semaphores->death);
	if (semaphores->full)
		sem_close(semaphores->full);
	if (semaphores->stop)
		sem_close(semaphores->stop);
	if (semaphores->sem_state)
		sem_close(semaphores->sem_state);
	unlink_semaphores();
	free(semaphores);
}
