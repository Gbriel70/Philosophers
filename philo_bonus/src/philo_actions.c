/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcosta-m <gcosta-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:36:29 by gcosta-m          #+#    #+#             */
/*   Updated: 2025/02/17 10:36:33 by gcosta-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static void	take_forks(t_philo *philo)
{
	sem_wait(philo->data->semaphores->table);
	sem_wait(philo->data->semaphores->forks);
	print_action(philo, TAKE_FORK);
	sem_wait(philo->data->semaphores->forks);
	print_action(philo, TAKE_FORK);
	sem_post(philo->data->semaphores->table);
}

void	eating(t_philo *philo)
{
	int	action_time;

	take_forks(philo);
	sem_wait(philo->data->semaphores->sem_state);
	action_time = print_action(philo, EAT);
	philo->time_last_ate = action_time;
	sem_post(philo->data->semaphores->sem_state);
	philo->times_eaten++;
	if (philo->times_eaten == philo->data->config->times_must_eat)
		sem_post(philo->data->semaphores->full);
	ft_usleep(philo->data->config->time_to_eat * 1000);
	sem_post(philo->data->semaphores->forks);
	sem_post(philo->data->semaphores->forks);
}

void	sleeping(t_philo *philo)
{
	print_action(philo, SLEEP);
	ft_usleep(philo->data->config->time_to_sleep * 1000);
}

void	thinking(t_philo *philo)
{
	print_action(philo, THINK);
	usleep(500);
}

int	print_action(t_philo *philo, t_philo_action action)
{
	int	time_ms;

	sem_wait(philo->data->semaphores->print);
	time_ms = calc_elapsed_ms(philo->data->monitor->start_time);
	if (action == TAKE_FORK)
		printf("%d %d %s%s%s\n", time_ms, philo->id, GREEN, TAKE_FORK_MSG,
			RESET);
	else if (action == EAT)
		printf("%d %d %s%s%s\n", time_ms, philo->id, YELLOW, EAT_MSG, RESET);
	else if (action == SLEEP)
		printf("%d %d %s%s%s\n", time_ms, philo->id, BLUE, SLEEP_MSG, RESET);
	else if (action == THINK)
		printf("%d %d %s%s%s\n", time_ms, philo->id, MAGENTA, THINK_MSG, RESET);
	sem_post(philo->data->semaphores->print);
	return (time_ms);
}
