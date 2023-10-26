/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 13:44:14 by kle-rest          #+#    #+#             */
/*   Updated: 2023/10/26 13:58:42 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_is_number(char **av)
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

int	ft_check_int(int ac, char **av)
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
		if (ft_strlen(av[ac]) > 19)
			return (0);
		ac--;
	}
	return (1);
}