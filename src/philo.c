/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoto-su <ssoto-su@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 19:21:23 by ssoto-su          #+#    #+#             */
/*   Updated: 2025/11/14 14:15:53 by ssoto-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (validate_args(argc, argv) == 1)
	{
		printf("Error\n");
		return (1);
	}
	if (init_table(argc, argv, &table) == 1)
		return (1);
	if (mem_alloc(&table) == 1)
		return (1);
	if (init_forks(&table) == 1)
		return (1);
	if (init_philo(table.philos, &table) == 1)
		return (1);
	if (first_init_thread(&table) == 1)
		return (1);
	hollocaust_mutex(&table, table.num_philo);
	return (0);
}
