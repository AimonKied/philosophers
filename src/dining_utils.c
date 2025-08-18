/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 21:17:38 by swied             #+#    #+#             */
/*   Updated: 2025/08/18 21:44:46 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	update_meal_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->m_mealtime);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->m_mealtime);
}

void	increase_meals_eaten(t_philo *philo)
{
	pthread_mutex_lock(&philo->m_meals_eaten);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->m_meals_eaten);
}

int	single_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print);
	printf("%lu %d has taken a fork\n", get_time()
		- philo->data->time->start, philo->id);
	pthread_mutex_unlock(&philo->data->print);
	return (-1);
}

int	get_forks_even(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
	print_msg(philo, 0, philo->id);
	if (check_stop(philo->data) == -1)
	{
		pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
		return (-1);
	}
	pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
	print_msg(philo, 0, philo->id);
	return (0);
}

int	get_forks_odd(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
	print_msg(philo, 0, philo->id);
	if (check_stop(philo->data) == -1)
	{
		pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
		return (-1);
	}
	pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
	print_msg(philo, 0, philo->id);
	return (0);
}
