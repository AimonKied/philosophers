/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 14:21:31 by swied             #+#    #+#             */
/*   Updated: 2025/08/19 16:01:26 by swied            ###   ########.fr       */
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
		if (create_threads(data, i, monitor) != 0)
			return (-1);
		i++;
	}
	pthread_join(monitor, NULL);
	join_threads(data);
	return (0);
}

int	create_threads(t_data *data, int i, pthread_t monitor)
{
	if (pthread_create(&data->t[i], NULL,
			philo_routine, &data->philo[i]) != 0)
	{
		pthread_mutex_lock(&data->print);
		printf("Thread creation failed\n");
		pthread_mutex_unlock(&data->print);
		pthread_join(monitor, NULL);
		join_threads(data);
		return (-1);
	}
	if (pthread_create(&data->m[i], NULL, philo_monitor_routine,
			&data->philo[i]) != 0)
	{
		pthread_mutex_lock(&data->print);
		printf("Thread creation failed\n");
		pthread_mutex_unlock(&data->print);
		pthread_join(monitor, NULL);
		join_threads(data);
		return (-1);
	}
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
		if (philo_eat(philo, data) == -1)
			break ;
		if (philo_sleep(philo, data) == -1)
			break ;
		if (philo_think(philo) == -1)
			break ;
	}
	return (NULL);
}

void	*philo_monitor_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!check_stop(philo->data))
	{
		check_philo_meals(philo);
		pthread_mutex_lock(&philo->m_mealtime);
		if (get_time() - philo->last_meal_time
			> philo->data->table->time_to_die)
		{
			pthread_mutex_lock(&philo->data->print);
			if (!philo->data->stop_simulation)
				printf("%llu %d died\n", get_time() - philo->data->time->start,
					philo->id);
			philo->data->stop_simulation = 1;
			pthread_mutex_unlock(&philo->data->print);
			pthread_mutex_unlock(&philo->m_mealtime);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->m_mealtime);
		ft_usleep(500, philo->data);
	}
	return (NULL);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (!check_stop(data))
	{
		if (all_philos_finished(data))
		{
			pthread_mutex_lock(&data->stop_mutex);
			data->stop_simulation = 1;
			pthread_mutex_unlock(&data->stop_mutex);
			return (NULL);
		}
		ft_usleep(500, data);
	}
	return (NULL);
}
