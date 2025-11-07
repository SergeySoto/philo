/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoto-su <ssoto-su@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 11:59:28 by ssoto-su          #+#    #+#             */
/*   Updated: 2025/11/07 18:58:27 by ssoto-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	mem_alloc(t_data *table)
{
	table->philos = malloc(sizeof(t_philo) * table->philo_num);
	if (!table->philos)
	{
		printf("Error: Memory allocation failed\n");
		return (1);
	}
	table->forks = malloc(sizeof(pthread_mutex_t) * table->philo_num);
	if (!table->forks)
	{
		printf("Error: Memory allocation failed\n");
		free(table->philos);
		return (1);
	}
	return (0);
}

void	hollocaust_mutex(t_data *table)
{
	int	i;

	i = 0;
	while (i < table->philo_num)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	free(table->forks);
	free(table->philos);
}

long long	get_time(void)
{
	
}
