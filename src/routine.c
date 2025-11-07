/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoto-su <ssoto-su@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:53:42 by ssoto-su          #+#    #+#             */
/*   Updated: 2025/11/07 18:54:03 by ssoto-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		printf("%d has taken a fork\n", philo->id);
		pthread_mutex_lock(philo->right_fork);
		printf("%d has taken a fork\n", philo->id);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		printf("%d has taken a fork\n", philo->id);
		pthread_mutex_lock(philo->left_fork);
		printf("%d has taken a fork\n", philo->id);
	}
	printf("%d is eating\n", philo->id);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	*start_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	printf("Philosopher %d begins his routine\n", philo->id);
	while (1)
	{
		
	}
	return (NULL);
}
