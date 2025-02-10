/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_uitls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcosta-m <gcosta-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:33:35 by gcosta-m          #+#    #+#             */
/*   Updated: 2025/02/10 11:40:08 by gcosta-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_atoi(char *str)
{
	int	sign;
	int	num;

	sign = 1;
	num = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\v'
		|| *str == '\f' || *str == '\r')
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		num = num * 10 + (*str - '0');
		str++;
	}
	if ((*str != '\0') && (*str < '0' || *str > '9'))
		return (-1);
	return (sign * num);
}

short	valid_arguments(int ac, char **av)
{
	int	i;

	if (ac < 5 || ac > 6)
	{
		print_error("Usage: ./philo num_of_philosophers time_to_die time_to_eat \
		time_to_sleep [times_each_must_eat]");
		return (FALSE);
	}
	i = 1;
	while (i < ac)
	{
		if (ft_atoi(av[i]) <= 0 || ft_atoi(av[i]) > __INT_MAX__)
		{
			print_error("Error: argv[i] must be a positive integer or less than\
			 INT_MAX");
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

int	print_error(char *message)
{
	fprintf(stderr, "\033[31m%s\033[0m\n", message);
	exit(EXIT_FAILURE);
}
