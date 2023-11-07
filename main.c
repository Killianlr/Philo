/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 11:38:31 by kle-rest          #+#    #+#             */
/*   Updated: 2023/11/07 11:33:33 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

void	tamere(void)
{
	struct timeval start;
	struct timeval end;
	long	int	diff;

	gettimeofday(&start, NULL);
	usleep(10000);
	gettimeofday(&end, NULL);
	diff = (end.tv_usec - start.tv_usec) * 1e-3;
	printf("diff time = %ld\n", diff);
	printf("start sec = %ld\n", start.tv_sec);
	printf("end sec = %ld\n", end.tv_sec);
	printf("start usec = %ld\n", start.tv_usec);
	printf("end usec = %ld\n", end.tv_usec);
}

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
	init_data(data, ac, av);
	if (!init_mutex(data))
		return (free_mutex(data, "error mutex\n"));
	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (free_data(data, "error malloc philo\n"));
	philo = create_philo(data, philo);
	if (!philo)
		return (free_philo(data, philo, "error malloc philo\n"));
	print_info(data, philo);
	if (!init_thread(data))
		return (1);
	printf("\033[92mEVERYONE HAS TO EAT\033[0m\n");
	// tamere();
	// if (!start_dinner(philo))
	// 	printf("someone just die\n");
	return (0);
}