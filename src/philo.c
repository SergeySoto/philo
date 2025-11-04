/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoto-su <ssoto-su@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 19:21:23 by ssoto-su          #+#    #+#             */
/*   Updated: 2025/11/04 20:26:04 by ssoto-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_isspace(int c)
{
	if (c >= 7 && c <= 32)
		return (1);
	return (0);
}

long	ft_atol(char *str)
{
	int		i;
	int		symbol;
	long	res;

	res = 0;
	symbol = 1;
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			symbol *= -1;
		i++;
	}
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (-1);
		res = (res * 10) + (str[i] - '0');
		i++;
		if ((res * symbol) > INT_MAX)
			return (res);
	}
	return (res * symbol);
}

int	validate_args(int argc, char **argv)
{
	int	i;
	int	num;

	num = 0;
	if (argc < 5 || argc > 6)
	{
		printf("AAHHHHHHHHHHH nop\n");
		return (1);
	}
	i = 0;
	while (argv[i])
	{
		num = ft_atol(argv[i]);
		if (num <= 0)
			return (1);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	int	res = validate_args(argc, argv);
	if (res == 1)
	{
		printf("Error\n");
		return (0);
	}
	printf("%d\n", res);
	return (0);
}