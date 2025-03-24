/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcosta-m <gcosta-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:34:18 by gcosta-m          #+#    #+#             */
/*   Updated: 2025/03/24 09:58:24 by gcosta-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	init_philosophers(t_data *data);
static void	*philosopher_routine(void *arg);
static void	*monitor_philos_state(void *arg);
int			print_action(t_philo *philo, t_philo_action action);

void	simulate(t_data *data)
{
	int			i;
	pthread_t	monitor_thread;

	init_philosophers(data);
	i = -1;
	while (++i < data->config.nbr_philo)
	{
		if (pthread_create(&data->philos[i].philo_pthread, NULL,
				philosopher_routine, (void *)&data->philos[i]) != 0)
		{
			data->sim_state.end_sim = TRUE;
			break ;
		}
	}
	if (pthread_create(&monitor_thread, NULL, monitor_philos_state,
			(void *)data) != 0)
		data->sim_state.end_sim = TRUE;
	i = -1;
	while (++i < data->config.nbr_philo)
		pthread_join(data->philos[i].philo_pthread, NULL);
	pthread_join(monitor_thread, NULL);
	free(data->philos);
}

static void	init_philosophers(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->config.nbr_philo);
	if (!data->philos)
		print_error("Failed to allocate philos");
	i = -1;
	while (++i < data->config.nbr_philo)
	{
		data->philos[i].id = i;
		data->philos[i].time_last_ate = \
		calc_elapsed_ms(data->sim_state.start_time);
		data->philos[i].times_eaten = 0;
		data->philos[i].full = FALSE;
		data->philos[i].left_fork = &data->mutex.fork_mtx[i];
		data->philos[i].right_fork = &data->mutex.fork_mtx[(i + 1)
			% data->config.nbr_philo];
		data->philos[i].data = data;
	}
}

static void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->config.nbr_philo == 1)
	{
		print_action(philo, TAKE_FORK);
		ft_usleep(philo->data->config.time_to_die * 1000);
		while (!stop_simulation(philo, 0))
			;
		return (NULL);
	}
	while (!stop_simulation(philo, 0))
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

static void	*monitor_philos_state(void *arg)
{
	t_data	*data;
	short	should_stop;

	data = (t_data *)arg;
	while (1)
	{
		should_stop = simulation_should_stop(data);
		if (should_stop)
		{
			pthread_mutex_lock(&data->mutex.sim_status_mtx);
			data->sim_state.end_sim = TRUE;
			pthread_mutex_unlock(&data->mutex.sim_status_mtx);
			break ;
		}
		pthread_mutex_lock(&data->mutex.sim_status_mtx);
		should_stop = data->sim_state.end_sim;
		pthread_mutex_unlock(&data->mutex.sim_status_mtx);
		if (should_stop)
			break ;
		usleep(1000);
	}
	return (NULL);
}

int	print_action(t_philo *philo, t_philo_action action)
{
	int	time_action_ms;

	pthread_mutex_lock(&philo->data->mutex.print_mtx);
	time_action_ms = calc_elapsed_ms(philo->data->sim_state.start_time);
	if (!stop_simulation(philo, 0))
	{
		if (action == TAKE_FORK)
			printf("%d %d %s%s%s\n", time_action_ms, philo->id, GREEN,
				TAKE_FORK_MSG, R);
		else if (action == EAT)
			printf("%d %d %s%s%s\n", time_action_ms, philo->id, YELLOW, EAT_MSG,
				R);
		else if (action == SLEEP)
			printf("%d %d %s%s%s\n", time_action_ms, philo->id, BLUE, SLEEP_MSG,
				R);
		else if (action == THINK)
			printf("%d %d %s%s%s\n", time_action_ms, philo->id, MAGENTA,
				THINK_MSG, R);
		else if (action == DIE)
			printf("%d %d %s%s%s\n", time_action_ms, philo->id, RED, DIE_MSG,
				R);
	}
	pthread_mutex_unlock(&philo->data->mutex.print_mtx);
	return (time_action_ms);
}
