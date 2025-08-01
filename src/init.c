/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 15:22:16 by swied             #+#    #+#             */
/*   Updated: 2025/08/02 00:05:43 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	init_all(t_data *data)
{
	if (init_philo(data) == -1)
		return (-1);
	init_forks(data);
	if (init_mutex(data, 0) == -1)
		return (free(data->philo), -1);
	if (init_threads(data) == -1)
		return (free(data->philo), free(data->forks),
			free(data->stop_mutex), free(data->mealtime), -1);
	data->time = malloc(sizeof(t_time));
	if (!data->time)
	{
		free(data->philo);
		free(data->forks);
		free(data->stop_mutex);
		free(data->mealtime);
		printf("Alloc failed\n");
		return (-1);
	}
	return (0);
}

int	init_philo(t_data *data)
{
	int	num;

	num = 0;
	data->philo = malloc(sizeof(t_philo) * data->table->nb_philos);
	if (!data->philo)
		return (printf("Alloc failed\n"), -1);
	while (num < data->table->nb_philos)
	{
		data->philo[num].id = num + 1;
		data->philo[num].meals_eaten = 0;
		num++;
	}
	return (0);
}

void	init_forks(t_data *data)
{
	int	i;
	int	fork_counter;

	i = 0;
	fork_counter = 0;
	while (i < data->table->nb_philos - 1)
	{
		data->philo[i].left_fork = fork_counter;
		data->philo[i].right_fork = fork_counter + 1;
		i++;
		fork_counter++;
	}
	data->philo[i].left_fork = fork_counter;
	data->philo[i].right_fork = 0;
}

int	init_mutex(t_data *data, int i)
{
	data->forks = malloc(sizeof(pthread_mutex_t) * data->table->nb_philos);
	if (!data->forks)
		return (printf("Alloc failed\n"), -1);
	while (i < data->table->nb_philos)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	data->stop_mutex = malloc(sizeof(pthread_mutex_t));
	if (!data->stop_mutex)
		return (free(data->forks), printf("Alloc failed\n"), -1);
	pthread_mutex_init(data->stop_mutex, NULL);
	data->mealtime = malloc(sizeof(pthread_mutex_t));
	if (!(data->mealtime))
	{
		free(data->forks);
		return (free(data->stop_mutex), printf("Alloc failed\n"), -1);
	}
	pthread_mutex_init(data->mealtime, NULL);
	data->print = malloc(sizeof(pthread_mutex_t));
	if (!data->print)
		return (free(data->forks), free(data->stop_mutex), free(data->mealtime),
			printf("Alloc failed\n"), -1);
	pthread_mutex_init(data->print, NULL);
	return (0);
}

int	init_threads(t_data *data)
{
	data->t = malloc(sizeof(pthread_t) * data->table->nb_philos);
	if (!data->t)
		return (printf("Alloc failed\n"), -1);
	return (0);
}
