/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcosta-m <gcosta-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:10:20 by gcosta-m          #+#    #+#             */
/*   Updated: 2025/02/17 10:44:04 by gcosta-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

int	get_current_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	calc_elapsed_ms(int start_time_ms)
{
	return (get_current_time_ms() - start_time_ms);
}

int	calc_elapsed_usec(int start_time_ms)
{
	int	elapsed_time_ms;

	elapsed_time_ms = get_current_time_ms() - start_time_ms;
	return (elapsed_time_ms * 1000);
}

void	ft_usleep(int usec_sleep_time)
{
	int	start_time_ms;
	int	usec_left;

	start_time_ms = get_current_time_ms();
	while ((calc_elapsed_usec(start_time_ms) < usec_sleep_time))
	{
		usec_left = usec_sleep_time - calc_elapsed_usec(start_time_ms);
		if (usec_left > 1000)
			usleep(usec_left / 2);
	}
}
