/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoto-su <ssoto-su@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 19:38:54 by ssoto-su          #+#    #+#             */
/*   Updated: 2025/11/13 19:52:50 by ssoto-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo	t_philo;

typedef struct t_table
{
	int				num_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_meals;
	long long		start_time;
	int				someone_died;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	meal_mutex;
	pthread_t		waiter_thread;
}	t_table;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long long		last_meal_time;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_table			*table;
}	t_philo;

int			start_simulation(int argc, char **argv, t_table *table);
void *		one_notes(void *arg);
//Parse
int			ft_isdigit(int c);
int			ft_isspace(int c);
long		ft_atol(char *str);
int			validate_args(int argc, char **argv);
//Inits
int			init_table(int argc, char **argv, t_table *table);
int			init_philo(t_philo *philo, t_table *table);
int			init_threads(t_table *table);
int			init_forks(t_table *table);
int			init_mutex(t_table *table);
//Utils
int			mem_alloc(t_table *table);
int			hollocaust_mutex(t_table *table, int size);
long long	get_time(void);
void		precise_time(long long time);
void		print_pthread(t_philo *philo, char *str);
//Routine
void		*start_routine(void *arg);
void		eat_routine(t_philo *philo);
void		sleep_routine(t_philo *philo);
void		think_routine(t_philo *philo);
int			safe_init_thread(t_table *table);
//Monitor
void		*waiter_routine(void *arg);
int			check_death(t_philo *philo);


#endif