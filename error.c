/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 13:23:09 by kle-rest          #+#    #+#             */
/*   Updated: 2023/11/21 18:09:49 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	free_mutex(t_data *data, char *msg)
{
	if (!data->fork)
	{
		free(data);
		return (1);
	}
	if (!data->philock)
	{
		free(data->fork);
		free(data);
		return (1);
	}
	printf("ici\n");
	if (data->writeon)
		pthread_mutex_destroy(&data->write);
	if (data->deathon)
		pthread_mutex_destroy(&data->death);
	free_data(data, "");
	printf("%s\n", msg);
	return (1);
}

int	free_data(t_data *data, char *msg)
{
	printf("%s", msg);
	free(data->fork);
	free(data->philock);
	free(data);
	return (1);
}

int	free_philo(t_data *data, t_philo *philo, char *msg)
{
	t_philo	*tmp;

	philo = data->philo;
	tmp = philo;
	printf("%s\n", msg);
	while (philo)
	{
		tmp = philo;
		philo = philo->next;
		free(tmp);
	}
	free(data->fork);
	free(data->philock);
	free(data);
	return (1);
}

int	error_thread(t_data *data, t_philo *philo, char *msg)
{
	printf("%s\n", msg);
	data->is_dead = 1;
	thread_join(data);
	ft_free_end(data, philo);
	return (1);
}
