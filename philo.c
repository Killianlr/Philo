/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 14:06:27 by kle-rest          #+#    #+#             */
/*   Updated: 2023/11/21 18:21:49 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(t_data *data, int ac, char **av)
{
	data->philo_nb = ft_atoi_long(av[1]);
	data->death_time = ft_atoi_long(av[2]);
	data->eat_time = ft_atoi_long(av[3]);
	data->sleep_time = ft_atoi_long(av[4]);
	data->meal_nb = -1;
	data->is_dead = 0;
	data->fork = NULL;
	data->philock = NULL;
	data->writeon = 0;
	data->deathon = 0;
	if (ac == 6)
		data->meal_nb = ft_atoi_long(av[5]);
	if (data->meal_nb == 0)
		return (1);
	if (data->philo_nb == 1)
	{
		printf("0 \033[90mphilo 1 \033[93mhas taken a fork\033[0m\n");
		printf("%ld \033[90mphilo 1 \033[91mdied\033[0m\n", data->death_time);
		return (1);
	}
	return (0);
}

static int	init_mutex3(t_data *data)
{
	if (pthread_mutex_init(&data->write, NULL) != 0)
	{
		data->writeon = 1;
		return (0);
	}
	if (pthread_mutex_init(&data->death, NULL) != 0)
	{
		data->deathon = 1;
		return (0);
	}
	return (1);
}

static int	init_mutex_tab(pthread_mutex_t *mutex, int i)
{
	int	s;

	s = 1;
	while (s < i)
	{
		if (s == 5)
		{
			return (s);
		}
		if (pthread_mutex_init(&mutex[s], NULL) != 0)
			return (s);
		s++;
	}
	printf("s = %d\n", s);
	return (s);
}

static int	init_mutex2(t_data *data, int i)
{
	int	mi;

	mi = 0;
	mi = init_mutex_tab(data->fork, i);
	if (mi != i)
	{
		while (--mi)
		{
			printf("mi = %d\n", mi);
			pthread_mutex_destroy(&data->fork[mi]);
		}
		return (0);
	}
	mi = init_mutex_tab(data->philock, i);
	if (mi != i)
	{
		while (--mi)
			pthread_mutex_destroy(&data->philock[mi]);
		return (0);
	}
	return (1);
}

int	init_mutex(t_data *data)
{
	int	i;

	i = data->philo_nb;
	data->fork = malloc(sizeof(pthread_mutex_t) * data->philo_nb);
	if (!data->fork)
		return (0);
	data->philock = malloc(sizeof(pthread_mutex_t) * data->philo_nb);
	if (!data->philock)
		return (0);
	if (!init_mutex2(data, i))
		return (0);
	if (!init_mutex3(data))
		return (0);
	return (1);
}

void	init_philo(t_data *data, t_philo *philo, int i)
{
	philo->id = i;
	philo->th = 0;
	philo->eat_count = 0;
	philo->time_to_die = data->death_time;
	philo->data = data;
	philo->start_time = data->start_time;
	philo->is_dead = &data->is_dead;
	philo->philock = data->philock[philo->id - 1];
	if (philo->id == 1)
	{
		philo->l_fork = &data->fork[philo->id - 1];
		philo->r_fork = &data->fork[data->philo_nb - 1];
	}
	else
	{
		philo->l_fork = &data->fork[philo->id - 1];
		philo->r_fork = &data->fork[philo->id - 2];
	}
}

t_philo	*create_philo(t_data *data, t_philo *philo)
{
	int	i;

	i = 2;
	data->philo = philo;
	data->start_time = get_time();
	init_philo(data, philo, 1);
	while (i <= data->philo_nb)
	{
		philo->next = malloc(sizeof(t_philo));
		if (!philo->next)
			return (data->philo);
		philo = philo->next;
		init_philo(data, philo, i);
		i++;
	}
	philo->next = data->philo;
	return (data->philo);
}
