/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 11:38:31 by kle-rest          #+#    #+#             */
/*   Updated: 2023/11/17 16:31:11 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_end(t_data *data, t_philo *philo)
{
	int		i;
	t_philo	*tmp;
	
	i = 0;
	while (philo && i < data->philo_nb)
	{
		tmp = philo->next;
		free(philo);
		philo = tmp;
		i++;
	}
	free(data->fork);
	free(data->philock);
	free(data);
}

int	main(int ac, char **av)
{
	t_data	*data;
	t_philo	*philo;

	if (!check_params(ac, av))
		return (1);
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (printf("error malloc data"));
	if (init_data(data, ac, av))
		return (free_data(data, ""));
	if (!init_mutex(data))
		return (free_mutex(data, "error mutex"));
	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (free_data(data, "error malloc philo"));
	philo = create_philo(data, philo);
	if (!philo)
		return (free_philo(data, philo, "error malloc philo"));
	print_info(data);
	if (!init_thread(data))
		return (error_thread(data, philo, "error thread"));
	ft_end(data, philo);
	return (0);
}
