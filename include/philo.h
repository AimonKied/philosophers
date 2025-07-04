/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:11:20 by swied             #+#    #+#             */
/*   Updated: 2025/07/04 15:38:38 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	PHILO_H
# define PHILO_H

# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <stdint.h>

typedef struct s_data t_data;

typedef struct s_philo
{
	int		id;
	int		meals_eaten;
	int		left_fork;
	int		right_fork;
	long	last_meal_time;
	t_data	*data;
}	t_philo;

typedef struct s_table
{
	int			nb_philos;
	int			index;
	int			reps;
	u_int64_t	time_to_die;
	u_int64_t	time_to_eat;
	u_int64_t	time_to_sleep;
}	t_table;

typedef struct s_time
{
	u_int64_t	start;
	u_int64_t	now;
}	t_time;

typedef struct s_data
{
	t_table			*table;
	t_philo			*philo;
	t_time			*time;
	int				stop_simulation;
	pthread_mutex_t	*mealtime;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*stop_mutex;
	pthread_mutex_t	*print;
	pthread_t		*t;
}	t_data;

int	main(int argc, char **argv);

int	check_arg(char *arg);
int	check_input(char **argv);
int	check_dead(t_data *data);

int	fill_data(int argc, char **argv, t_data *data);

int	ft_atoi(const char *str);
uint64_t	get_time();
void	get_first_meal(t_data *data);
int	check_stop(t_data *data);

void	free_table(t_data *data);
void	destroy_mutex(t_data *data);

int		init_all(t_data *data);
int		init_philo(t_data *data);
void	init_forks(t_data *data);
int		init_mutex(t_data *data);
int		init_threads(t_data *data);

// void *test_mutex(void *arg);
int	execute(t_data *data);
void	*monitor_routine(void *arg);
// int	check_stop(t_data *data);

int	philo_eat_even(t_philo *philo);
int	philo_eat_odd(t_philo *philo);
int	philo_sleep(t_philo *philo);
int philo_think(t_philo *philo);

#endif