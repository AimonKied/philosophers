/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 14:31:56 by swied             #+#    #+#             */
/*   Updated: 2025/08/18 20:43:04 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	philo_eat(t_philo *philo, t_data *data)
{
	if (philo->left_fork == philo->right_fork)
		return (single_philo(philo));
	if (check_stop(philo->data) == -1)
		return (-1);
	get_forks(philo);
	if (check_stop(philo->data) == -1)
		return (-1);
	print_msg(philo, 1, philo->id);
	pthread_mutex_lock(&philo->m_mealtime);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->m_mealtime);
	if (ft_usleep(philo->data->table->time_to_eat * 1000, data) == -1)
	{
		pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
		pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
		return (-1);
	}
	pthread_mutex_lock(&philo->m_meals_eaten);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->m_meals_eaten);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	return (0);
}

int	philo_sleep(t_philo *philo, t_data *data)
{
	if (check_stop(philo->data) == -1)
		return (-1);
	print_msg(philo, 2, philo->id);
	if (ft_usleep(philo->data->table->time_to_sleep * 1000, data) == -1)
		return (-1);
	return (0);
}

int	philo_think(t_philo *philo)
{
	if (check_stop(philo->data) == -1)
		return (-1);
	print_msg(philo, 3, philo->id);
	if (check_stop(philo->data) == -1)
		return (-1);
	return (0);
}

void	get_forks(t_philo *philo)
{
	if (philo->id % 2 != 0)
	{
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
		print_msg(philo, 0, philo->id);
		if (check_stop(philo->data) == -1)
		{
			pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
			return ;
		}
		pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
		print_msg(philo, 0, philo->id);
	}
	else
	{
		pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
		print_msg(philo, 0, philo->id);
		if (check_stop(philo->data) == -1)
		{
			pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
			return ;
		}
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
		print_msg(philo, 0, philo->id);
	}
}

int	single_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print);
	printf("%lu %d has taken a fork\n", get_time()
		- philo->data->time->start, philo->id);
	pthread_mutex_unlock(&philo->data->print);
	return (-1);
}
