/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoto-su <ssoto-su@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:53:42 by ssoto-su          #+#    #+#             */
/*   Updated: 2025/11/11 17:35:40 by ssoto-su         ###   ########.fr       */
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
	philo->last_meal_time = get_time();
	philo->meals_eaten++;
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

void	*start_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		eat_routine(philo);
		sleep_routine(philo);
		think_routine(philo);
	}
	return (NULL);
}
