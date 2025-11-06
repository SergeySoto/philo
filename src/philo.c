/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoto-su <ssoto-su@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 19:21:23 by ssoto-su          #+#    #+#             */
/*   Updated: 2025/11/06 20:08:27 by ssoto-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*start_routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	printf("Philosopher %d begins his routine\n", philo->id);
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_data	table;

	if (validate_args(argc, argv) == 1)
	{
		printf("Error\n");
		return (1);
	}
	if (init_all(argc, argv, &table) == 1)
	{
		hollocaust_mutex(&table);
		return (1);
	}
	hollocaust_mutex(&table);
	return (0);
}
