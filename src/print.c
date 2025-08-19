/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 01:34:02 by swied             #+#    #+#             */
/*   Updated: 2025/08/19 16:01:07 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	print_msg(t_philo *philo, int flag, int id)
{
	if (philo->data->stop_simulation)
		return ;
	pthread_mutex_lock(&philo->data->print);
	if (flag == 0)
	{
		printf("%llu %d has taken a fork\n", get_time()
			- philo->data->time->start, id);
	}
	else if (flag == 1)
	{
		printf("%llu %d is eating\n", get_time()
			- philo->data->time->start, id);
	}
	else if (flag == 2)
	{
		printf("%llu %d is sleeping\n", get_time()
			- philo->data->time->start, id);
	}
	else if (flag == 3)
	{
		printf("%llu %d is thinking\n", get_time()
			- philo->data->time->start, id);
	}
	pthread_mutex_unlock(&philo->data->print);
}
