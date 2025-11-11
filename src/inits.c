/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoto-su <ssoto-su@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 15:59:34 by ssoto-su          #+#    #+#             */
/*   Updated: 2025/11/11 20:10:52 by ssoto-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	init_table(int argc, char **argv, t_table *table)
{
	table->num_philo = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]);
	table->time_to_eat = ft_atol(argv[3]);
	table->time_to_sleep = ft_atol(argv[4]);
	table->start_time = get_time();
	table->someone_died = 0;
	if (argc == 6)
		table->num_meals = ft_atol(argv[5]);
	else
		table->num_meals = -1;
	if (pthread_mutex_init(&table->print_mutex, NULL) != 0)
	{
		printf("Error: initializing mutex\n");
		return (1);
	}
	if (pthread_mutex_init(&table->death_mutex, NULL) != 0)
	{
		printf("Error: initializing mutex\n");
		return (1);
	}
	if (pthread_mutex_init(&table->meal_mutex, NULL) != 0)
	{
		printf("Error: initializing mutex\n");
		return (1);
	}
	return (0);
}

void	init_philo(t_philo *philo, t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philo)
	{
		philo[i].id = i + 1;
		philo[i].meals_eaten = 0;
		philo[i].last_meal_time = table->start_time;
		philo[i].left_fork = &table->forks[i];
		philo[i].right_fork = &table->forks[(i + 1) % table->num_philo];
		philo[i].table = table;
		i++;
	}
}

int	init_forks(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philo)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
		{
			printf("Error: initializing mutex\n");
			return (hollocaust_mutex(table, i));
		}
		i++;
	}
	return (0);
}

int	init_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philo)
	{
		if (pthread_create(&table->philos[i].thread, NULL, &start_routine, &table->philos[i]) != 0)
			return (hollocaust_mutex(table, table->num_philo));
		i++;
	}
	if (pthread_create(&table->waiter_thread, NULL, &waiter_routine, table) != 0)
		return (hollocaust_mutex(table, table->num_philo));
	if (pthread_join(&table->waiter_thread, NULL) != 0)
		return (hollocaust_mutex(table, table->num_philo));
	i = 0;
	while (i < table->num_philo)
	{
		if (pthread_join(table->philos[i].thread, NULL) != 0)
			return (hollocaust_mutex(table, table->num_philo));
		i++;
	}
	return (0);
}

int	init_all(int argc, char **argv, t_table *table)
{
	if (init_table(argc, argv, table) == 1)
		return (1);
	if (mem_alloc(table) == 1)
		return (1);
	init_philo(table->philos, table);
	if (init_forks(table) == 1)
		return (1);
	if (init_threads(table) == 1)
		return (1);
	return (0);
}
