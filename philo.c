/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 14:06:27 by kle-rest          #+#    #+#             */
/*   Updated: 2023/10/31 14:42:11 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_data(t_data *data, int ac, char **av)
{
	data->philo_nb = ft_atoi_long(av[1]);
	data->death_time = ft_atoi_long(av[2]);
	data->eat_time = ft_atoi_long(av[3]);
	data->sleep_time = ft_atoi_long(av[4]);
	data->meal_nb = 0;
	if (ac == 6)
		data->meal_nb = ft_atoi_long(av[5]);
	data->dead = 0;
	data->start_time = 0;
}

int	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	data->fork = malloc(sizeof(pthread_mutex_t) * data->philo_nb);
	if (!data->fork)
		return (0);
	while (i < data->philo_nb)
	{
		if (pthread_mutex_init(&data->fork[i], NULL) != 0)
			return (0);
		i++;
	}
	if (pthread_mutex_init(&data->lock, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&data->write, NULL) != 0)
		return (0);
	return (1);
}

void	init_philo(t_data *data, t_philo *philo, int i)
{
	philo->id = i;
	philo->eat_count = 0;
	philo->status = 0;
	philo->time_to_die = data->death_time;
	philo->data = data;
	if (philo->id == 1)
	{
		philo->l_fork = &data->fork[data->philo_nb - 1];
		philo->r_fork = &data->fork[0];
	}
	else
	{
		philo->l_fork = &data->fork[philo->id - 1];
		philo->r_fork = &data->fork[philo->id - 2];
	}
}

t_philo	*create_philo(t_data *data, t_philo *philo)
{
	t_philo *first;
	int	i;

	i = 2;
	init_philo(data, philo, 1);
	first = philo;
	while (i <= data->philo_nb)
	{
		philo->next = malloc(sizeof(t_philo));
		if(!philo)
			return (NULL);
		// printf("philo->id = %d, i = %d\n", philo->id, i);
		philo = philo->next;
		init_philo(data, philo, i);
		i++;
	}
	philo->next = NULL;
	return (first);
}
