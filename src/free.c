/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 11:12:13 by swied             #+#    #+#             */
/*   Updated: 2025/08/15 20:36:25 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	free_everything(t_data *data)
{
	free(data->philo);
	free(data->forks);
	free(data->time);
	free(data->table);
	free(data->t);
}

void	destroy_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->table->nb_philos)
	{
		pthread_join(data->t[i], NULL);
		i++;
	}
	i = 0;
	while (i < data->table->nb_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->stop_mutex);
	pthread_mutex_destroy(&data->mealtime);
	pthread_mutex_destroy(&data->print);
	printf("kaka\n");
}
