/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 01:34:02 by swied             #+#    #+#             */
/*   Updated: 2025/08/15 20:21:23 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	print_msg(t_philo *philo, int flag, int id)
{
	pthread_mutex_lock(&philo->data->print);
	if (flag == 0)
	{
		printf("%lu %d has taken a fork\n", get_time()
			- philo->data->time->start, id);
	}
	else if (flag == 1)
	{
		printf("%lu %d is eating\n", get_time()
			- philo->data->time->start, id);
	}
	else if (flag == 2)
	{
		printf("%lu %d is sleeping\n", get_time()
			- philo->data->time->start, id);
	}
	else if (flag == 3)
	{
		printf("%lu %d is thinking\n", get_time()
			- philo->data->time->start, id);
	}
	pthread_mutex_unlock(&philo->data->print);
}

void	put_str(char *str)
{
	while (*str)
	{
		write(1, "str", 1);
	}
}
