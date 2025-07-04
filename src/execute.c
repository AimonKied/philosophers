/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 14:21:31 by swied             #+#    #+#             */
/*   Updated: 2025/07/04 18:30:02 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (check_stop(philo->data) == -1)
			break ;
		if (philo->left_fork < philo->right_fork)
		{
			if (philo_eat(philo, 1) == -1)
				break ;
		}
		else
		{
			if (philo_eat(philo, 2) == -1)
				break ;
		}
		philo_sleep(philo);
		if (check_stop(philo->data) == -1)
			break ;
		philo_think(philo);
		if (check_stop(philo->data) == -1)
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
			pthread_mutex_lock(data->stop_mutex);
			data->stop_simulation = 1;
			pthread_mutex_unlock(data->stop_mutex);
			break ;
		}
		ft_usleep(1000);
	}
	return (NULL);
}

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
	return (0);
}
