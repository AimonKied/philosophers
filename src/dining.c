/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 14:31:56 by swied             #+#    #+#             */
/*   Updated: 2025/07/04 15:41:04 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	philo_eat_even(t_philo *philo)
{
	if (check_stop(philo->data) == -1)
		return (-1);
	pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
	pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
	pthread_mutex_lock(philo->data->print);
	printf("%lu %d has taken a fork\n", get_time() - philo->data->time->start, philo->id);
	printf("%lu %d has taken a fork\n", get_time() - philo->data->time->start, philo->id);
	pthread_mutex_unlock(philo->data->print);
	if (check_stop(philo->data) == -1)
	{
		pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
		pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
		return (-1);
	}
	pthread_mutex_lock(philo->data->mealtime);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(philo->data->mealtime);
	if (check_stop(philo->data) == -1)
	{
		pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
		pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
		return (-1);
	}
	pthread_mutex_lock(philo->data->print);
	printf("%lu %d is eating\n", get_time() - philo->data->time->start, philo->id);
	pthread_mutex_unlock(philo->data->print);
	usleep(philo->data->table->time_to_eat * 1000);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	if (check_stop(philo->data) == -1)
		return (-1);
	return (0);
}

int	philo_eat_odd(t_philo *philo)
{
	if (check_stop(philo->data) == -1)
		return (-1);
	// usleep(1000);
	pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
	pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
	pthread_mutex_lock(philo->data->print);
	printf("%lu %d has taken a fork\n", get_time() - philo->data->time->start, philo->id);
	printf("%lu %d has taken a fork\n", get_time() - philo->data->time->start, philo->id);
	pthread_mutex_unlock(philo->data->print);
	if (check_stop(philo->data) == -1)
	{
		pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
		pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
		return (-1);
	}
	pthread_mutex_lock(philo->data->mealtime);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(philo->data->mealtime);
	if (check_stop(philo->data) == -1)
	{
		pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
		pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
		return (-1);
	}
	pthread_mutex_lock(philo->data->print);
	printf("%lu %d is eating\n", get_time() - philo->data->time->start, philo->id);
	pthread_mutex_unlock(philo->data->print);
	usleep(philo->data->table->time_to_eat * 1000);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	if (check_stop(philo->data) == -1)
		return(-1);
	return (0);
}

int	philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(philo->data->print);
	printf("%lu %d is sleeping\n", get_time() - philo->data->time->start, philo->id);
	pthread_mutex_unlock(philo->data->print);
	usleep(philo->data->table->time_to_sleep * 1000);
	if (check_stop(philo->data) == -1)
		return (-1);
	return (0);
}

int philo_think(t_philo *philo)
{
	pthread_mutex_lock(philo->data->print);
	printf("%lu %d is thinking\n", get_time() - philo->data->time->start, philo->id);
	pthread_mutex_unlock(philo->data->print);
	if (check_stop(philo->data) == -1)
		return (-1);
	return (0);
}
