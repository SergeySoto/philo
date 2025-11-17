/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoto-su <ssoto-su@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 11:59:28 by ssoto-su          #+#    #+#             */
/*   Updated: 2025/11/17 20:26:35 by ssoto-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	mem_alloc(t_table *table)
{
	table->philos = malloc(sizeof(t_philo) * table->num_philo);
	if (!table->philos)
	{
		printf("Error: Memory allocation failed\n");
		pthread_mutex_destroy(&table->print_mutex);
		pthread_mutex_destroy(&table->death_mutex);
		pthread_mutex_destroy(&table->meal_mutex);
		return (1);
	}
	table->forks = malloc(sizeof(pthread_mutex_t) * table->num_philo);
	if (!table->forks)
	{
		printf("Error: Memory allocation failed\n");
		free(table->philos);
		pthread_mutex_destroy(&table->print_mutex);
		pthread_mutex_destroy(&table->death_mutex);
		pthread_mutex_destroy(&table->meal_mutex);
		return (1);
	}
	return (0);
}

int	hollocaust_mutex(t_table *table, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&table->print_mutex);
	pthread_mutex_destroy(&table->death_mutex);
	pthread_mutex_destroy(&table->meal_mutex);
	free(table->forks);
	free(table->philos);
	return (1);
}

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	precise_time(t_philo *philo, long long time)
{
	long long	start;
	long long	current_time;

	start = get_time();
	while (1)
	{
		if (death_row(philo) == 1)
			return ;
		current_time = get_time();
		if (current_time - start >= time)
			break ;
		usleep(500);
	}
}

void	print_pthread(t_philo *philo, char *str)
{
	long long	time;

	pthread_mutex_lock(&philo->table->death_mutex);
	if (philo->table->someone_died == 1)
	{
		pthread_mutex_unlock(&philo->table->death_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->table->death_mutex);
	pthread_mutex_lock(&philo->table->print_mutex);
	time = get_time() - philo->table->start_time;
	printf("%lld %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(&philo->table->print_mutex);
}
