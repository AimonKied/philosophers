/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:26:46 by swied             #+#    #+#             */
/*   Updated: 2025/08/14 23:46:41 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	check_input(char **argv)
{
	if (check_arg(argv[1]) == -1)
		return (printf("Wrong input for Philosopher\n"), -1);
	if (check_arg(argv[2]) == -1)
		return (printf("Wrong input for time to die\n"), -1);
	if (check_arg(argv[3]) == -1)
		return (printf("Wrong input for time to eat\n"), -1);
	if (check_arg(argv[4]) == -1)
		return (printf("Wrong input for time to sleep\n"), -1);
	if (argv[5])
		if (check_arg(argv[5]) == -1)
			return (printf("Wrong input for amount of times eating\n"), -1);
	return (0);
}

int	check_arg(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (-1);
		i++;
	}
	return (0);
}

int	check_dead(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->table->nb_philos)
	{
		pthread_mutex_lock(data->mealtime);
		if (get_time() - data->philo[i].last_meal_time
			> data->table->time_to_die)
		{
			pthread_mutex_lock(data->stop_mutex);
			data->stop_simulation = 1;
			pthread_mutex_unlock(data->stop_mutex);
			if (data->philo[i].meals_eaten == data->table->reps)
				return (pthread_mutex_unlock(data->mealtime), -1);
			printf("%lu %d died\n", get_time()
				- data->time->start, data->philo[i].id);
			pthread_mutex_unlock(data->mealtime);
			return (-1);
		}
		pthread_mutex_unlock(data->mealtime);
		i++;
	}
	return (0);
}
