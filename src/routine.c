/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoto-su <ssoto-su@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:53:42 by ssoto-su          #+#    #+#             */
/*   Updated: 2025/11/17 20:26:58 by ssoto-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	eat_routine(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_pthread(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_pthread(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_pthread(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_pthread(philo, "has taken a fork");
	}
	print_pthread(philo, "is eating");
	pthread_mutex_lock(&philo->table->meal_mutex);
	philo->last_meal_time = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->table->meal_mutex);
	precise_time(philo, philo->table->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	sleep_routine(t_philo *philo)
{
	if (death_row(philo) == 1)
		return ;
	print_pthread(philo, "is sleeping");
	precise_time(philo, philo->table->time_to_sleep);
}

void	think_routine(t_philo *philo)
{
	long long	time_to_think;

	if (death_row(philo) == 1)
		return ;
	print_pthread(philo, "is thinking");
	if (philo->table->num_philo % 2 != 0)
	{
		time_to_think = (philo->table->time_to_eat * 2)
			- philo->table->time_to_sleep;
		if (time_to_think < 0)
			time_to_think = 0;
		if (time_to_think > 0)
			precise_time(philo, time_to_think);
		else
			usleep(1000);
	}
	else
		usleep(1000);
}

void	*one_notes(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	print_pthread(philo, "has taken a fork");
	precise_time(philo, philo->table->time_to_die);
	print_pthread(philo, "died");
	return (0);
}

void	*start_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(500);
	while (1)
	{
		if (death_row(philo) == 1)
			return (NULL);
		eat_routine(philo);
		if (death_row(philo) == 1)
			return (NULL);
		sleep_routine(philo);
		if (death_row(philo) == 1)
			return (NULL);
		think_routine(philo);
	}
	return (NULL);
}
