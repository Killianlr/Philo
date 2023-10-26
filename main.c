/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 11:38:31 by kle-rest          #+#    #+#             */
/*   Updated: 2023/10/26 14:18:40 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac < 5 || ac > 6)
		return (printf("Wrong number of arguments\n"));
	if (!ft_is_number(av))
		return (printf("invalid argument\n"));
	if (!ft_check_int(ac, av))
		return (printf("error int overflow\n"));
	data = (t_data *)malloc(sizeof(t_data));
	if(!data)
		return (printf("error malloc data\n"));
	set_data(data, ac, av);
	print(data);
	return (0);
}