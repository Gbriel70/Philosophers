/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcosta-m <gcosta-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:10:14 by gcosta-m          #+#    #+#             */
/*   Updated: 2025/02/10 18:02:15 by gcosta-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

int	main(int ac, char **av)
{
	t_data *data;
	int i;

	if (!valid_arguments(ac, av))
		print_error("Error: Invalid arguments");
	data = init(ac, av);
	i = -1;
	while (++i < data->config->nbr_philos)
	{
		data->philo_pid[i] = ft_fork(data);
		if (data->philo_pid[i] == 0)
			philo_routine(&data, i);
	}
	error_exit("kill everything", data, 4);
	return (0);
}