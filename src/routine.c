/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoto-su <ssoto-su@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:53:42 by ssoto-su          #+#    #+#             */
/*   Updated: 2025/11/14 14:04:32 by ssoto-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	eat_routine(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
		print_pthread(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->left_fork);
		print_pthread(philo, "has taken a fork");
	}
	print_pthread(philo, "is eating");
	precise_time(philo->table->time_to_eat);
	pthread_mutex_lock(&philo->table->death_mutex);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->table->death_mutex);
	pthread_mutex_lock(&philo->table->meal_mutex);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->table->meal_mutex);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	sleep_routine(t_philo *philo)
{
	print_pthread(philo, "is sleeping");
	precise_time(philo->table->time_to_sleep);
}

void	think_routine(t_philo *philo)
{
	print_pthread(philo, "is thinking");
}

void	*one_notes(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	print_pthread(philo, "has taken a fork");
	precise_time(philo->table->time_to_die);
	print_pthread(philo, "died");
	return (0);
}

void	*start_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(philo->table->time_to_eat * 500);
	while (1)
	{
		if (philo->table->someone_died == 1)
			return (NULL);
		eat_routine(philo);
		sleep_routine(philo);
		think_routine(philo);
	}
	return (NULL);
}
