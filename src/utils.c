/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 16:06:01 by swied             #+#    #+#             */
/*   Updated: 2025/07/04 14:20:53 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	nb;
	int	sign;

	i = 0;
	nb = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == ' '))
		i++;
	if (str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb *= 10;
		nb += str[i] - '0';
		i++;
	}
	return (nb * sign);
}

uint64_t	get_time()
{
	struct timeval	tv;
	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
}

void	get_first_meal(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->table->nb_philos)
	{
		data->philo[i].data = data;
		pthread_mutex_lock(data->mealtime);
		data->philo[i].last_meal_time = data->time->start;
		pthread_mutex_unlock(data->mealtime);
		i++;
	}
}

int	check_stop(t_data *data)
{
	pthread_mutex_lock(data->stop_mutex);
	if (data->stop_simulation)
	{
		pthread_mutex_unlock(data->stop_mutex);
		return (-1);
	}
	pthread_mutex_unlock(data->stop_mutex);
	return (0);
}
