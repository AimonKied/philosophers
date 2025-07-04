/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:43:02 by swied             #+#    #+#             */
/*   Updated: 2025/07/04 14:00:15 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	fill_data(int argc, char **argv, t_data *data)
{
	data->table = malloc(sizeof(t_table));
	if (!data->table)
		return (printf("Alloc failed\n"), -1);
	data->table->nb_philos = ft_atoi(argv[1]);
	data->table->time_to_die = ft_atoi(argv[2]);
	data->table->time_to_eat = ft_atoi(argv[3]);
	data->table->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->table->reps = ft_atoi(argv[5]);
	else
		data->table->reps = -1;
	data->stop_simulation = 0;
	return (0);
}
