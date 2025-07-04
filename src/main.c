/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:09:26 by swied             #+#    #+#             */
/*   Updated: 2025/07/04 18:12:10 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (printf("Wrong amount of arguments\n"), 0);
	if (check_input(argv) == -1)
		return (0);
	if (fill_data(argc, argv, &data) == -1)
		return (1);
	if (init_all(&data) == -1)
		return (1);
	execute(&data);
	printf("\nExecute done\n");
	free_table(&data);
	return (0);
}
