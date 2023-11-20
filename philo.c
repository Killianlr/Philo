/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 14:06:27 by kle-rest          #+#    #+#             */
/*   Updated: 2023/11/17 16:25:38 by kle-rest         ###   ########.fr       */
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
	if (ac == 6)
		data->meal_nb = ft_atoi_long(av[5]);
	if (data->philo_nb == 1)
	{
		printf("0 \033[90mphilo 1 \033[93mhas taken a fork\033[0m\n");
		printf("0 \033[90mphilo 1 \033[93mhas taken a fork\033[0m\n");
		printf("0 \033[90mphilo 1 \033[92mis eating\033[0m\n");
		printf("%ld \033[90mphilo 1 \033[91mdied\033[0m", data->death_time);
		return (1);
	}
	return (0);
}

int	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	data->fork = malloc(sizeof(pthread_mutex_t) * data->philo_nb);
	if (!data->fork)
		return (0);
	data->philock = malloc(sizeof(pthread_mutex_t) * data->philo_nb);
	if (!data->philock)
		return (0);
	while (i < data->philo_nb)
	{
		if (pthread_mutex_init(&data->fork[i], NULL) != 0)
			return (0);
		if (pthread_mutex_init(&data->philock[i], NULL) != 0)
			return (0);
		i++;
	}
	if (pthread_mutex_init(&data->write, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&data->death, NULL) != 0)
		return (0);
	return (1);
}

void	init_philo(t_data *data, t_philo *philo, int i)
{
	philo->id = i;
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
		if (!philo)
			return (NULL);
		philo = philo->next;
		init_philo(data, philo, i);
		i++;
	}
	philo->next = data->philo;
	return (data->philo);
}

void	end(t_philo *philo, int philo_full)
{
	pthread_mutex_lock(&philo->data->death);
	*philo->is_dead = 1;
	pthread_mutex_unlock(&philo->data->death);
	if (philo_full != philo->data->philo_nb)
	{
		pthread_mutex_lock(&philo->data->write);
		printf("%ldms \033[90mphilo %d \033[91mdied\033[0m\n",
			curenttime(philo->start_time), philo->id);
		pthread_mutex_unlock(&philo->data->write);
	}
}

int		check_death(t_philo *philo)
{
	int	dying;

	pthread_mutex_lock(&philo->data->death);
	dying = *philo->is_dead;
	pthread_mutex_unlock(&philo->data->death);
	return (dying);
}

void	*funeral(void *arg)
{
	t_philo *philo;
	int		philo_full;

	philo = (t_philo *)arg;
	philo_full = 0;
	while (philo && !check_death(philo))
	{
		pthread_mutex_lock(&philo->philock);
		if (philo->id == 1)
			philo_full = 0;
		if (philo->eat_count >= philo->data->meal_nb)
			philo_full++;


		if ((philo->time_to_die < curenttime(philo->start_time))
			|| philo_full == philo->data->philo_nb)
				end(philo, philo_full);


		pthread_mutex_unlock(&philo->philock);
		philo = philo->next;
	}
	return (NULL);
}

int	init_philo_impair(t_philo *philo)
{
	int	i;

	i = 1;
	philo = philo->next;
	while (philo && i < philo->data->philo_nb)
	{
		if (pthread_create(&philo->th, NULL, &start_dinner, philo) != 0)
			return (0);
		philo = philo->next->next;
		i += 2;
	}
	return (0);
}

int	init_philo_pair(t_philo *philo)
{
	int	i;

	i = 0;
	while (philo && i < philo->data->philo_nb)
	{
		if (pthread_create(&philo->th, NULL, &start_dinner, philo) != 0)
			return (0);
		philo = philo->next->next;
		i += 2;
	}
	return (0);
}

int	init_thread(t_data *data)
{
	t_philo	*philo;
	int		i;

	philo = data->philo;
	if (data->philo_nb % 2 == 1)
	{
		init_philo_pair(philo);
		usleep(100);
		philo = data->philo;
		init_philo_impair(philo);
	}
	else
	{
		init_philo_impair(philo);
		usleep(100);
		philo = data->philo;
		init_philo_pair(philo);
	}
	if (pthread_create(&data->check, NULL, &funeral, data->philo) != 0)
			return (0);
	i = 0;
	philo = data->philo;
	while (philo && i < philo->data->philo_nb)
	{
		if (pthread_join(philo->th, NULL) != 0)
			return (0);
		philo = philo->next;
		i++;
	}
	if (pthread_join(data->check, NULL) != 0)
			return (0);
	return (1);
}
