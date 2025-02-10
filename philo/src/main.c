/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcosta-m <gcosta-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:33:22 by gcosta-m          #+#    #+#             */
/*   Updated: 2025/02/10 11:42:33 by gcosta-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int ac, char **av)
{
	t_data	*data;

	if (!valid_arguments(ac, av))
		return (print_error("Invalid arguments"));
	data = init(ac, av);
	simulate(data);
	destroy_mutexes(&data->mutex, data->config.nbr_philo, 5);
	free(data);
	return (0);
}
