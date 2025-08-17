/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:11:20 by swied             #+#    #+#             */
/*   Updated: 2025/08/16 15:36:38 by swied            ###   ########.fr       */
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
	uint64_t	time_to_die;
	uint64_t	time_to_eat;
	uint64_t	time_to_sleep;
}	t_table;

typedef struct s_time
{
	uint64_t	start;
	uint64_t	now;
}	t_time;

typedef struct s_data
{
	t_table			*table;
	t_philo			*philo;
	t_time			*time;
	int				stop_simulation;
	pthread_mutex_t	mealtime;
	pthread_mutex_t	*forks;
	pthread_mutex_t	stop_mutex;
	pthread_mutex_t	print;
	pthread_t		*t;
	pthread_t		*m;
}	t_data;

int			main(int argc, char **argv);

//check.c
int			check_arg(char *arg);
int			check_input(char **argv);
int			check_dead(t_data *data);

//parsing.c
int			fill_data(int argc, char **argv, t_data *data);

//utils.c
int			ft_atoi(const char *str);
uint64_t	get_time(void);
void		get_first_meal(t_data *data);
int			check_stop(t_data *data);
int			ft_usleep(uint64_t time, t_data *data);
void		join_threads(t_data *data);

//free.c
void		free_table(t_data *data);
void		destroy_mutex(t_data *data);
void		free_everything(t_data *data);

//init.c
int			init_all(t_data *data);
int			init_philo(t_data *data);
void		init_forks(t_data *data);
int			init_mutex(t_data *data);
int			init_threads(t_data *data);

//execute.c
int			execute(t_data *data);
void		*monitor_routine(void *arg);
void		*philo_routine(void *arg);
void		*philo_monitor_routine(void *arg);

//dining.c
int			philo_eat(t_philo *philo, t_data *data);
void		get_forks(t_philo *philo);
int			philo_sleep(t_philo *philo, t_data *data);
int			philo_think(t_philo *philo);

//print.c
void		print_msg(t_philo *philo, int flag, int id);
#endif