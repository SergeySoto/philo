/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoto-su <ssoto-su@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 11:59:28 by ssoto-su          #+#    #+#             */
/*   Updated: 2025/11/05 15:28:02 by ssoto-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	mem_alloc(t_data *table)
{
	table->philos = malloc(sizeof(t_philo) * table->philo_num);
	if (!table->philos)
	{
		printf("No has alocado loca\n");
		exit(1);
	}
	table->forks = malloc(sizeof(pthread_mutex_t) * table->philo_num);
	if (!table->forks)
	{
		pritnf("Usa el tenedor, mal educado\n");
		free(table->philos);
		exit(1);
	}
}
