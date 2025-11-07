/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoto-su <ssoto-su@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 15:59:34 by ssoto-su          #+#    #+#             */
/*   Updated: 2025/11/07 16:54:07 by ssoto-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	init_table(int argc, char **argv, t_data *table)
{
	table->philo_num = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]);
	table->time_to_eat = ft_atol(argv[3]);
	table->time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
		table->meals_num = ft_atol(argv[5]);
	else
		table->meals_num = -1;
}

void	init_philo(t_philo *philo, t_data *table)
{
	int	i;

	i = 0;
	while (i < table->philo_num)
	{
		philo[i].id = i + 1;
		philo[i].meals_eaten = 0;
		philo[i].last_meal_time = 0;
		philo[i].left_fork = &table->forks[i];
		philo[i].right_fork = &table->forks[(i + 1) % table->philo_num];
		philo[i].data = table;
		i++;
	}
}

int	init_forks(t_data *table)
{
	int	i;

	i = 0;
	while (i < table->philo_num)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
		{
			printf("Error: initializing mutex\n");
			hollocaust_mutex(table);
			return (1);
		}
		i++;
	}
	return (0);
}

int	init_all(int argc, char **argv, t_data *table)
{
	int	i;

	init_table(argc, argv, table);
	if (mem_alloc(table) == 1)
		return (1);
	init_philo(table->philos, table);
	if (init_forks(table) == 1)
		return (1);
	i = 0;
	while (i < table->philo_num)
	{
		if (pthread_create(&table->philos[i].thread, NULL, &start_routine, &table->philos[i]) != 0)
			return (1);
		i++;
	}
	i = 0;
	while (i < table->philo_num)
	{
		if (pthread_join(table->philos[i].thread, NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}
