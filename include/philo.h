/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:11:20 by swied             #+#    #+#             */
/*   Updated: 2025/08/18 22:50:16 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <stdint.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	int				left_fork;
	int				right_fork;
	int				eat_enough;
	pthread_mutex_t	m_eat_enough;
	pthread_mutex_t	m_meals_eaten;
	pthread_mutex_t	m_mealtime;
	long			last_meal_time;
	t_data			*data;
}	t_philo;

typedef struct s_table
{
	int				nb_philos;
	int				index;
	int				reps;
	uint64_t		time_to_die;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
}	t_table;

typedef struct s_time
{
	uint64_t		start;
	uint64_t		now;
}	t_time;

typedef struct s_data
{
	t_table			*table;
	t_philo			*philo;
	t_time			*time;
	int				stop_simulation;
	pthread_mutex_t	*forks;
	pthread_mutex_t	stop_mutex;
	pthread_mutex_t	print;
	pthread_t		*t;
	pthread_t		*m;
}	t_data;

int			main(int argc, char **argv);

//check.c
int			check_input(char **argv);
int			check_arg(char *arg);
int			check_stop(t_data *data);

//dining.c
int			philo_eat(t_philo *philo, t_data *data);
int			philo_sleep(t_philo *philo, t_data *data);
int			philo_think(t_philo *philo);
int			get_forks(t_philo *philo);
int			single_philo(t_philo *philo);

//execute.c
int			execute(t_data *data);
void		*philo_routine(void *arg);
void		*philo_monitor_routine(void *arg);
void		*monitor_routine(void *arg);
int			create_threads(t_data *data, int i, pthread_t monitor);

//free.c
void		free_everything(t_data *data);
void		destroy_mutex(t_data *data);

//init.c
int			init_all(t_data *data);
int			init_philo(t_data *data);
void		init_forks(t_data *data);
int			init_mutex(t_data *data);
int			init_threads(t_data *data);

//parsing.c
int			fill_data(int argc, char **argv, t_data *data);

//print.c
void		print_msg(t_philo *philo, int flag, int id);

//utils.c
int			ft_atoi(const char *str);
uint64_t	get_time(void);
void		get_first_meal(t_data *data);
int			ft_usleep(uint64_t time, t_data *data);
void		join_threads(t_data *data);

//dining_utils.c
void		update_meal_time(t_philo *philo);
void		increase_meals_eaten(t_philo *philo);
int			get_forks_even(t_philo *philo);
int			get_forks_odd(t_philo *philo);

//execute_utils.c
void		check_philo_meals(t_philo *philo);
int			all_philos_finished(t_data *data);
#endif