/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 11:12:13 by swied             #+#    #+#             */
/*   Updated: 2025/07/04 18:21:07 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	free_everything(t_data *data)
{
	destroy_mutex(data);
	
}

void	free_table(t_data *data)
{
	if (data->table)
		free(data->table);
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