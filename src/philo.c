/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoto-su <ssoto-su@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 19:21:23 by ssoto-su          #+#    #+#             */
/*   Updated: 2025/11/05 16:44:23 by ssoto-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	main(int argc, char **argv)
{
	t_data	table;
	t_philo	philo;

	if (validate_args(argc, argv) == 1)
	{
		printf("Error\n");
		return (1);
	}
	return (0);
}
