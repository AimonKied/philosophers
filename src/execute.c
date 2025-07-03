/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 14:21:31 by swied             #+#    #+#             */
/*   Updated: 2025/07/03 17:20:28 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*philo_routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	t_data  *data = philo->data;

	while (1)
	{
		// Check if simulation should stop
		pthread_mutex_lock(data->stop_mutex);
		if (data->stop_simulation)
		{
			pthread_mutex_unlock(data->stop_mutex);
			break;
		}
		pthread_mutex_unlock(data->stop_mutex);

		// Take forks (always in the same order to avoid deadlock)
		if (philo->id % 2 == 0)
		{
			pthread_mutex_lock(&data->forks[philo->left_fork]);
			pthread_mutex_lock(&data->forks[philo->right_fork]);
			pthread_mutex_lock(data->print);
			printf("%llu %d has taken a fork\n", get_time() - data->time->start, philo->id);
			printf("%llu %d has taken a fork\n", get_time() - data->time->start, philo->id);
			if (data->stop_simulation)
			{
				pthread_mutex_unlock(data->print);
				break;
			}
			pthread_mutex_unlock(data->print);
		}
		else
		{
			pthread_mutex_lock(&data->forks[philo->right_fork]);
			pthread_mutex_lock(&data->forks[philo->left_fork]);
			pthread_mutex_lock(data->print);
			printf("%llu %d has taken a fork\n", get_time() - data->time->start, philo->id);
			printf("%llu %d has taken a fork\n", get_time() - data->time->start, philo->id);
			if (data->stop_simulation)
			{
				pthread_mutex_unlock(data->print);
				break;
			}
			pthread_mutex_unlock(data->print);
		}

		// Eating
		pthread_mutex_lock(data->mealtime);
		philo->last_meal_time = get_time();
		pthread_mutex_unlock(data->mealtime);


		pthread_mutex_lock(data->print);
		printf("%llu %d is eating\n", get_time() - data->time->start, philo->id);
		pthread_mutex_unlock(data->print);

		usleep(data->table->time_to_eat * 1000);

		philo->meals_eaten++;

		pthread_mutex_unlock(&data->forks[philo->left_fork]);
		pthread_mutex_unlock(&data->forks[philo->right_fork]);

		// Schlafen
		pthread_mutex_lock(data->print);
		printf("%llu %d is sleeping\n", get_time() - data->time->start, philo->id);
		pthread_mutex_unlock(data->print);
		usleep(data->table->time_to_sleep * 1000);

		// Denken
		pthread_mutex_lock(data->print);
		printf("%llu %d is thinking\n", get_time() - data->time->start, philo->id);
		pthread_mutex_unlock(data->print);
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
	int			i;

	data->time = malloc(sizeof(t_time));
	if (!data->time)
		return (printf("Alloc failed\n"), -1);
	data->time->start = get_time();

	// Initialisiere last_meal_time für alle Philosophen
	i = 0;
	while (i < data->table->nb_philos)
	{
		data->philo[i].data = data;
		pthread_mutex_lock(data->mealtime);
		data->philo[i].last_meal_time = data->time->start;
		pthread_mutex_unlock(data->mealtime);
		i++;
	}

	// Starte Philosophen-Threads
	i = 0;
	while (i < data->table->nb_philos)
	{
		if (pthread_create(&data->t[i], NULL, philo_routine, &data->philo[i]) != 0)
			return (printf("Thread creation failed\n"), -1);
		i++;
	}

	// Starte Monitor-Thread (optional, für Tod-Erkennung)
	pthread_t monitor;
	pthread_create(&monitor, NULL, monitor_routine, data);

	// Warte auf alle Philosophen
	i = 0;
	while (i < data->table->nb_philos)
	{
		pthread_join(data->t[i], NULL);
		i++;
	}

	pthread_join(monitor, NULL);
	return 0;
	}
