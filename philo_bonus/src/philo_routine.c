/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcosta-m <gcosta-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:36:39 by gcosta-m          #+#    #+#             */
/*   Updated: 2025/02/17 10:36:41 by gcosta-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static char	*get_unique_name(t_philo *philo, char *name)
{
	char	*semaphore_name;
	char	*id_str;

	id_str = ft_utoa(philo->id);
	semaphore_name = ft_strjoin(name, id_str);
	free(id_str);
	return (semaphore_name);
}

static void	init_philo(t_philo *philo, t_data *data, int i)
{
	philo->data = data;
	philo->id = i + 1;
	philo->time_last_ate = calc_elapsed_ms(philo->data->monitor->start_time);
	philo->times_eaten = 0;
	philo->sem_state_name = get_unique_name(philo, "state");
	sem_unlink(philo->sem_state_name);
	philo->data->semaphores->sem_state = sem_open(philo->sem_state_name,
			O_CREAT, 0660, 1);
}

static void	*self_monitor(void *arg)
{
	t_philo	*philo;
	int		current_time;
	int		time_hungry;

	philo = (t_philo *)arg;
	while (1)
	{
		sem_wait(philo->data->semaphores->sem_state);
		current_time = calc_elapsed_ms(philo->data->monitor->start_time);
		time_hungry = current_time - philo->time_last_ate;
		if (time_hungry > philo->data->config->time_to_die)
		{
			sem_wait(philo->data->semaphores->print);
			printf("%d %d %s%s%s\n", current_time, philo->id, RED, "died",
				RESET);
			sem_post(philo->data->semaphores->death);
			break ;
		}
		sem_post(philo->data->semaphores->sem_state);
		usleep(500);
	}
	return (NULL);
}

void	philo_routine(t_data *data, int i)
{
	t_philo	philo;

	init_philo(&philo, data, i);
	pthread_create(&philo.self_monitor, NULL, self_monitor, (void *)&philo);
	pthread_detach(philo.self_monitor);
	if (philo.data->config->nbr_philos == 1)
	{
		print_action(&philo, TAKE_FORK);
		ft_usleep(philo.data->config->time_to_die * 1000);
	}
	if (philo.id % 2 == 0)
		thinking(&philo);
	while (1)
	{
		eating(&philo);
		sleeping(&philo);
		thinking(&philo);
	}
}
