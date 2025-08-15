/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:09:26 by swied             #+#    #+#             */
/*   Updated: 2025/08/15 20:06:37 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
	{
		printf("Wrong amount of args\n"
			"Usage:./philo philosophers time_to_die time_to_eat "
			"time_to_sleep [how_often_eat]\n");
		return (0);
	}
	if (check_input(argv) == -1)
		return (0);
	if (fill_data(argc, argv, &data) == -1)
		return (1);
	if (init_all(&data) == -1)
		return (free(data.table), 1);
	if (execute(&data) == -1)
		return (destroy_mutex(&data), free_everything(&data), 1);
	free_everything(&data);
	destroy_mutex(&data);
	return (0);
}
