/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoto-su <ssoto-su@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 19:38:54 by ssoto-su          #+#    #+#             */
/*   Updated: 2025/11/05 16:34:04 by ssoto-su         ###   ########.fr       */
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

typedef struct s_data
{
	int				philo_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_num;
	t_philo			*philos;
	pthread_mutex_t	*forks;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long			last_meal_time;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
}	t_philo;

//Parse
int		ft_isdigit(int c);
int		ft_isspace(int c);
long	ft_atol(char *str);
int		validate_args(int argc, char **argv);
//Inits
void	init_table(int argc, char **argv, t_data *table);
void	init_philo(t_philo *philo, t_data *table);
void	init_forks(t_data *table);

//Utils
void	mem_alloc(t_data *table);

#endif