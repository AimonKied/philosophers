/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:26:46 by swied             #+#    #+#             */
/*   Updated: 2025/08/17 20:47:33 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	check_input(char **argv)
{
	if (!argv[1] || check_arg(argv[1]) == -1)
		return (printf("Wrong input for Philosopher\n"), -1);
	if (!argv[2] || check_arg(argv[2]) == -1)
		return (printf("Wrong input for time to die\n"), -1);
	if (!argv[3] || check_arg(argv[3]) == -1)
		return (printf("Wrong input for time to eat\n"), -1);
	if (!argv[4] || check_arg(argv[4]) == -1)
		return (printf("Wrong input for time to sleep\n"), -1);
	if (argv[5] && check_arg(argv[5]) == -1)
			return (printf("Wrong input for amount of times eating\n"), -1);
	return (0);
}

int	check_arg(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (-1);
		i++;
	}
	return (0);
}

int	check_stop(t_data *data)
{
	if (!data)
		return (-1);
	pthread_mutex_lock(&data->stop_mutex);
	if (data->stop_simulation)
	{
		pthread_mutex_unlock(&data->stop_mutex);
		return (-1);
	}
	pthread_mutex_unlock(&data->stop_mutex);
	return (0);
}
