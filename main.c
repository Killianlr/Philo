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

void	ft_end(t_data *data, t_philo *philo)
{
	int	i;
	t_philo	*tmp;

	i = data->philo_nb;
	while (i--)
	{
		tmp = philo->next;
		free(philo);
		philo = tmp;
	}
	free(philo);
	free(data->fork);
	free(data);
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
	ft_end(data, philo);
	return (0);
}