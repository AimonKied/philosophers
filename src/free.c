/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 11:12:13 by swied             #+#    #+#             */
/*   Updated: 2025/08/18 20:37:30 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	free_everything(t_data *data)
{
	if (!data)
		return ;
	if (data->philo)
		free(data->philo);
	if (data->forks)
		free(data->forks);
	if (data->time)
		free(data->time);
	if (data->table)
		free(data->table);
	if (data->t)
		free(data->t);
	if (data->m)
		free(data->m);
}

void	destroy_mutex(t_data *data)
{
	int	i;

	if (!data)
		return ;
	if (data->table && data->forks)
	{
		i = 0;
		while (i < data->table->nb_philos)
		{
			pthread_mutex_destroy(&data->forks[i]);
			pthread_mutex_destroy(&data->philo[i].m_eat_enough);
			pthread_mutex_destroy(&data->philo[i].m_meals_eaten);
			pthread_mutex_destroy(&data->philo[i].m_mealtime);
			i++;
		}
	}
	pthread_mutex_destroy(&data->stop_mutex);
	pthread_mutex_destroy(&data->print);
}

