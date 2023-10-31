/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 11:38:31 by kle-rest          #+#    #+#             */
/*   Updated: 2023/10/31 14:26:55 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

int	main(int ac, char **av)
{
	t_data	*data;
	t_philo	*philo;

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
	if (!init_mutex(data))
	{
		return (1);
	}
	philo = malloc(sizeof(t_philo));
	if (!philo)
	{
		return (1);
	}
	philo = create_philo(data, philo);
	if (!philo)
	{
		return (1);
	}
	print_info(data, philo);
	if (!start_dinner(philo))
		printf("someone just die\n");
	// gettime();
	return (0);
}