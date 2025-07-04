/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 14:21:31 by swied             #+#    #+#             */
/*   Updated: 2025/07/04 15:03:26 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*philo_routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	t_data  *data = philo->data;

	while (1)
	{
		if (check_stop(data) == -1)
			break;
		if (philo->id % 2 == 0)
		{
			if (philo_eat_even(philo) == -1)
				break;
		}
		else
		{
			if (philo_eat_odd(philo) == -1)
				break;
		}
		philo_sleep(philo);
		philo_think(philo);
	}
	return NULL;
	}

void	*monitor_routine(void *arg)
{
	t_data *data = (t_data *)arg;

	while (1)
	{
		if (check_dead(data) == -1)
		{
			pthread_mutex_lock(data->stop_mutex);
			data->stop_simulation = 1;
			pthread_mutex_unlock(data->stop_mutex);
			break;
		}
		usleep(1000);
	}
	return(NULL);
}

int	execute(t_data *data)
{
	int	i;
	pthread_t monitor;

	data->time->start = get_time();
	get_first_meal(data);
	pthread_create(&monitor, NULL, monitor_routine, data);
	i = 0;
	while (i < data->table->nb_philos)
	{
		if (pthread_create(&data->t[i], NULL, philo_routine, &data->philo[i]) != 0)
			return (printf("Thread creation failed\n"), -1);
		i++;
	}
	i = 0;
	while (i < data->table->nb_philos)
	{
		pthread_join(data->t[i], NULL);
		i++;
	}
	pthread_join(monitor, NULL);
	return 0;
}

