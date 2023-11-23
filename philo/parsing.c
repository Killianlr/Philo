/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 13:44:14 by kle-rest          #+#    #+#             */
/*   Updated: 2023/11/23 12:14:55 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	ft_atoi_long(const char *nptr)
{
	int			i;
	long int	s;
	long int	nb;

	nb = 0;
	i = 0;
	s = 1;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		nb *= 10;
		nb += nptr[i] - 48;
		i++;
	}
	return (s * nb);
}

static int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static int	ft_is_number(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if ((av[i][j] < 48) || (av[i][j] > 57))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

static int	ft_check_int(int ac, char **av)
{
	unsigned long long	tmp;

	if (ac == 6)
	{
		if (ft_strlen(av[5]) > 10)
			return (0);
		tmp = ft_atoi_long(av[5]);
		if (tmp > __INT_MAX__)
			return (0);
		ac--;
	}
	if (ft_strlen(av[1]) > 10)
		return (0);
	tmp = ft_atoi_long(av[1]);
	if (tmp > __INT_MAX__)
		return (0);
	ac--;
	while (ac > 1)
	{
		if (ft_strlen(av[ac]) > 9)
			return (0);
		ac--;
	}
	return (1);
}

int	check_params(int ac, char **av)
{
	if (ac < 5 || ac > 6)
	{
		printf("Wrong number of arguments\n");
		return (0);
	}
	if (!ft_is_number(av))
	{
		printf("invalid argument\n");
		return (0);
	}
	if (!ft_check_int(ac, av))
	{
		printf("error int overflow\n");
		return (0);
	}
	return (1);
}
