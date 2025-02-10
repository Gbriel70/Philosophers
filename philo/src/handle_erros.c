/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_erros.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcosta-m <gcosta-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:33:46 by gcosta-m          #+#    #+#             */
/*   Updated: 2025/02/10 11:33:48 by gcosta-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	destroy_mutexes(t_mutex *mutex, int nbr_philo, int stage)
{
	int	i;

	if (stage >= 2)
	{
		pthread_mutex_destroy(&mutex->print_mtx);
		if (stage >= 3)
		{
			pthread_mutex_destroy(&mutex->time_ate_mtx);
			if (stage >= 4)
			{
				pthread_mutex_destroy(&mutex->philos_full_mtx);
				if (stage == 5)
					pthread_mutex_destroy(&mutex->sim_status_mtx);
			}
		}
	}
	i = -1;
	while (++i < nbr_philo)
		pthread_mutex_destroy(&mutex->fork_mtx[i]);
	free(mutex->fork_mtx);
}

short	stop_simulation(t_philo *philo, int stop)
{
	short	status;

	pthread_mutex_lock(&philo->data->mutex.sim_status_mtx);
	if (stop)
		philo->data->sim_state.end_sim = TRUE;
	status = philo->data->sim_state.end_sim;
	pthread_mutex_unlock(&philo->data->mutex.sim_status_mtx);
	return (status);
}

short	simulation_should_stop(t_data *data)
{
	int	i;
	int	current_time_ms;

	i = -1;
	current_time_ms = calc_elapsed_ms(data->sim_state.start_time);
	while (++i < data->config.nbr_philo)
	{
		if ((current_time_ms
				- data->philos[i].time_last_ate) > data->config.time_to_die)
		{
			pthread_mutex_lock(&data->mutex.print_mtx);
			printf("%d %d %s%s\n", current_time_ms, data->philos[i].id, RED,
				DIE_MSG);
			pthread_mutex_unlock(&data->mutex.print_mtx);
			return (TRUE);
		}
	}
	if (data->config.nbr_must_eat > 0 && all_philos_full(data->philos))
		return (TRUE);
	return (FALSE);
}
