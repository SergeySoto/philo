/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoto-su <ssoto-su@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 14:06:18 by ssoto-su          #+#    #+#             */
/*   Updated: 2025/11/14 16:58:48 by ssoto-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	second_init_thread(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philo)
	{
		if (pthread_create(&table->philos[i].thread,
				NULL, &start_routine, &table->philos[i]) != 0)
			return (hollocaust_mutex(table, table->num_philo));
		i++;
	}
	if (pthread_create(&table->waiter_thread,
			NULL, &waiter_routine, table) != 0)
		return (hollocaust_mutex(table, table->num_philo));
	return (0);
}

int	first_init_thread(t_table *table)
{
	int	i;

	i = 0;
	if (table->num_philo == 1)
	{
		pthread_create(&table->philos[0].thread,
			NULL, &one_notes, &table->philos[0]);
		pthread_join(table->philos[0].thread, NULL);
		return (0);
	}
	if (second_init_thread(table) == 1)
		return (1);
	if (pthread_join(table->waiter_thread, NULL) != 0)
		return (hollocaust_mutex(table, table->num_philo));
	while (i < table->num_philo)
	{
		if (pthread_join(table->philos[i].thread, NULL) != 0)
			return (hollocaust_mutex(table, table->num_philo));
		i++;
	}
	return (0);
}
