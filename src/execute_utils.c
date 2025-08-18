/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 22:38:02 by swied             #+#    #+#             */
/*   Updated: 2025/08/18 22:50:36 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	check_philo_meals(t_philo *philo)
{
	pthread_mutex_lock(&philo->m_eat_enough);
	pthread_mutex_lock(&philo->m_meals_eaten);
	if (philo->meals_eaten >= philo->data->table->reps
		&& !philo->eat_enough)
	{
		philo->eat_enough = 1;
	}
	pthread_mutex_unlock(&philo->m_eat_enough);
	pthread_mutex_unlock(&philo->m_meals_eaten);
}

int	all_philos_finished(t_data *data)
{
	int	i;
	int	finished;

	i = 0;
	finished = 0;
	while (i < data->table->nb_philos)
	{
		pthread_mutex_lock(&data->philo[i].m_eat_enough);
		if (data->philo[i].eat_enough)
			finished++;
		pthread_mutex_unlock(&data->philo[i].m_eat_enough);
		i++;
	}
	if (finished == data->table->nb_philos && data->table->reps > 0)
		return (1);
	return (0);
}
