/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 16:06:01 by swied             #+#    #+#             */
/*   Updated: 2025/08/16 15:04:16 by swied            ###   ########.fr       */
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

uint64_t	get_time(void)
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
		data->philo[i].last_meal_time = data->time->start;
		i++;
	}
}

int	ft_usleep(uint64_t time, t_data *data)
{
	uint64_t	start;
	uint64_t	elapsed;

	start = get_time();
	elapsed = get_time();
	while ((elapsed - start) * 1000 < time)
	{
		if (check_stop(data) == -1)
			return (-1);
		usleep(100);
		elapsed = get_time();
	}
	return (0);
}

void	join_threads(t_data *data)
{
	int	i;

	i = 0;
	if (data->t)
	{
		while (i < data->table->nb_philos && data->t[i])
		{
			pthread_join(data->t[i], NULL);
			i++;
		}
	}
	return ;
}
