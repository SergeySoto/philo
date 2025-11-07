/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoto-su <ssoto-su@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 19:21:23 by ssoto-su          #+#    #+#             */
/*   Updated: 2025/11/07 16:08:12 by ssoto-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	eat()
{
	
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
