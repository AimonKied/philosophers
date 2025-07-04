/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 14:31:56 by swied             #+#    #+#             */
/*   Updated: 2025/07/04 18:30:10 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	philo_eat(t_philo *philo, int flag)
{
	if (philo->left_fork == philo->right_fork)
		return (printf("%llu %d has taken a fork\n", get_time()
				- philo->data->time->start, philo->id), -1);
	get_forks(philo, flag);
	if (check_stop(philo->data) == -1)
		return (-1);
	pthread_mutex_lock(philo->data->print);
	printf("%llu %d has taken a fork\n", get_time()
		-philo->data->time->start, philo->id);
	printf("%llu %d has taken a fork\n", get_time()
		- philo->data->time->start, philo->id);
	pthread_mutex_unlock(philo->data->print);
	philo->last_meal_time = get_time();
	pthread_mutex_lock(philo->data->print);
	printf("%llu %d is eating\n", get_time()
		- philo->data->time->start, philo->id);
	pthread_mutex_unlock(philo->data->print);
	ft_usleep(philo->data->table->time_to_eat * 1000);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	if (check_stop(philo->data) == -1)
		return (-1);
	return (0);
}

int	philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(philo->data->print);
	printf("%llu %d is sleeping\n", get_time()
		- philo->data->time->start, philo->id);
	pthread_mutex_unlock(philo->data->print);
	ft_usleep(philo->data->table->time_to_sleep * 1000);
	if (check_stop(philo->data) == -1)
		return (-1);
	return (0);
}

int	philo_think(t_philo *philo)
{
	pthread_mutex_lock(philo->data->print);
	printf("%llu %d is thinking\n", get_time()
		- philo->data->time->start, philo->id);
	pthread_mutex_unlock(philo->data->print);
	if (check_stop(philo->data) == -1)
		return (-1);
	return (0);
}

void	get_forks(t_philo *philo, int flag)
{
	if (flag == 1)
	{
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
		pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
	}
	else if (flag == 2)
	{
		pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
	}
}
