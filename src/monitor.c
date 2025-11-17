/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoto-su <ssoto-su@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 19:38:52 by ssoto-su          #+#    #+#             */
/*   Updated: 2025/11/17 19:40:59 by ssoto-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	check_death(t_philo *philo)
{
	long long	current_time;
	long long	last_time;
	long long	time_w_food;

	current_time = get_time();
	pthread_mutex_lock(&philo->table->meal_mutex);
	last_time = philo->last_meal_time;
	pthread_mutex_unlock(&philo->table->meal_mutex);
	time_w_food = current_time - last_time;
	pthread_mutex_lock(&philo->table->death_mutex);
	if (time_w_food >= philo->table->time_to_die)
	{
		pthread_mutex_unlock(&philo->table->death_mutex);
		print_pthread(philo, "died");
		pthread_mutex_lock(&philo->table->death_mutex);
		philo->table->someone_died = 1;
		pthread_mutex_unlock(&philo->table->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->death_mutex);
	return (0);
}

int	check_all_ate(t_table *table)
{
	int	i;

	if (table->num_meals == -1)
		return (0);
	i = 0;
	while (i < table->num_philo)
	{
		pthread_mutex_lock(&table->meal_mutex);
		if (table->philos[i].meals_eaten < table->num_meals)
		{
			pthread_mutex_unlock(&table->meal_mutex);
			return (0);
		}
		pthread_mutex_unlock(&table->meal_mutex);
		i++;
	}
	return (1);
}

int	death_row(t_philo *philo)
{
	int	died;

	pthread_mutex_lock(&philo->table->death_mutex);
	died = philo->table->someone_died;
	pthread_mutex_unlock(&philo->table->death_mutex);
	return (died);
}

static void	axel_died(t_table *table)
{
	pthread_mutex_lock(&table->death_mutex);
	table->someone_died = 1;
	pthread_mutex_unlock(&table->death_mutex);
}

void	*waiter_routine(void *arg)
{
	t_table	*table;
	int		i;

	table = (t_table *)arg;
	if (table->num_philo == 1)
		return (NULL);
	while (1)
	{
		i = 0;
		while (i < table->num_philo)
		{
			if (check_death(&table->philos[i]) == 1)
			{
				print_pthread(&table->philos[i], "died");
				return (NULL);
			}
			i++;
		}
		if (check_all_ate(table) == 1)
		{
			axel_died(table);
			return (NULL);
		}
		usleep(100);
	}
}
