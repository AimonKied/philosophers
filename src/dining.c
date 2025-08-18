/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 14:31:56 by swied             #+#    #+#             */
/*   Updated: 2025/08/18 21:49:24 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	philo_eat(t_philo *philo, t_data *data)
{
	(void)data;
	if (philo->left_fork == philo->right_fork)
		return (single_philo(philo));
	if (check_stop(philo->data) == -1)
		return (-1);
	if (get_forks(philo) == -1)
		return (-1);
	if (check_stop(philo->data) == -1)
	{
		pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
		pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
		return (-1);
	}
	print_msg(philo, 1, philo->id);
	update_meal_time(philo);
	if (ft_usleep(philo->data->table->time_to_eat * 1000, data) == -1)
	{
		pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
		pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
		return (-1);
	}
	increase_meals_eaten(philo);
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

int	get_forks(t_philo *philo)
{
	if (philo->id % 2 != 0)
	{
		if (get_forks_even(philo) == -1)
			return (-1);
	}
	else
	{
		if (get_forks_odd(philo) == -1)
			return (-1);
	}
	return (0);
}
