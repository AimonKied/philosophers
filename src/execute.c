/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 14:21:31 by swied             #+#    #+#             */
/*   Updated: 2025/08/15 20:33:46 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	execute(t_data *data)
{
	int			i;
	pthread_t	monitor;

	data->time->start = get_time();
	get_first_meal(data);
	pthread_create(&monitor, NULL, monitor_routine, data);
	i = 0;
	while (i < data->table->nb_philos)
	{
		if (pthread_create(&data->t[i], NULL,
				philo_routine, &data->philo[i]) != 0)
			{
				pthread_mutex_lock(&data->print);
				printf("Thread creation failed\n");
				pthread_mutex_unlock(&data->print);
				pthread_join(monitor, NULL);
				return (-1);
			}
		i++;
	}
	pthread_join(monitor, NULL);
	return (0);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	while (1)
	{
		if (philo->data->table->reps >= philo->meals_eaten)
		{
			if (philo->data->table->reps == philo->meals_eaten)
				break ;
			if (check_stop(philo->data))
				break ;
		}
		if (philo_eat(philo, data) == -1)
			break ;
		if (philo_sleep(philo, data) == -1)
			break ;
		if (philo_think(philo) == -1)
			break ;
	}
	return (NULL);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		if (check_dead(data) == -1)
		{
			pthread_mutex_lock(&data->stop_mutex);
			data->stop_simulation = 1;
			pthread_mutex_unlock(&data->stop_mutex);
			break ;
		}
		ft_usleep(500, data);
	}
	return (NULL);
}
