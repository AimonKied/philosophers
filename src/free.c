/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 11:12:13 by swied             #+#    #+#             */
/*   Updated: 2025/08/01 23:11:03 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	free_everything(t_data *data)
{
	free(data->philo);
	free(data->forks);
	free(data->stop_mutex);
	free(data->mealtime);
	free(data->time);
	free(data->table);
	free(data->t);
	free(data->print);
}

void	destroy_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->table->nb_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
}
