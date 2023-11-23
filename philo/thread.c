/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:23:09 by kle-rest          #+#    #+#             */
/*   Updated: 2023/11/23 12:11:18 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_philo_impair(t_philo *philo)
{
	int	i;

	i = 1;
	philo = philo->next;
	while (philo && i < philo->data->philo_nb)
	{
		if (pthread_create(&philo->th, NULL, &routine_dinner, philo) != 0)
			return (0);
		philo = philo->next->next;
		i += 2;
	}
	return (1);
}

static int	init_philo_pair(t_philo *philo)
{
	int	i;

	i = 0;
	while (philo && i < philo->data->philo_nb)
	{
		if (pthread_create(&philo->th, NULL, &routine_dinner, philo) != 0)
			return (0);
		philo = philo->next->next;
		i += 2;
	}
	return (1);
}

int	thread_join(t_data *data)
{
	t_philo	*philo;
	int		i;

	philo = data->philo;
	i = 0;
	while (philo && i < philo->data->philo_nb)
	{
		if (philo->th)
		{
			if (pthread_join(philo->th, NULL) != 0)
				return (0);
		}
		philo = philo->next;
		i++;
	}
	if (pthread_join(data->check, NULL) != 0)
		return (0);
	return (1);
}

int	init_thread(t_data *data, t_philo *philo)
{
	if (data->philo_nb % 2 == 1)
	{
		if (!init_philo_pair(philo))
			return (0);
		usleep(100);
		philo = data->philo;
		if (!init_philo_impair(philo))
			return (0);
	}
	else
	{
		if (!init_philo_impair(philo))
			return (0);
		usleep(100);
		philo = data->philo;
		if (!init_philo_pair(philo))
			return (0);
	}
	if (pthread_create(&data->check, NULL, &routine_death, data->philo) != 0)
		return (0);
	if (!thread_join(data))
		return (0);
	return (1);
}
