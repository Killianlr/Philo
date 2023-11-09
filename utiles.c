/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 12:00:54 by kle-rest          #+#    #+#             */
/*   Updated: 2023/11/09 12:19:34 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	int	get_time(void)
{
	struct timeval	start;

	gettimeofday(&start, NULL);
	return (start.tv_sec * 1000 + start.tv_usec / 1000);
}

long	int	curenttime(long int start)
{
	return (get_time() - start);
}

int	checkdeath(long int death_time, long int curent_time, t_philo *philo)
{
	if (!philo->data->dead)
	{
		pthread_mutex_unlock(&philo->data->lock);
		return (1);
	}
	if (death_time < curent_time)
	{
		printf("%ldms \033[90mphilo %d \033[91mdied\033[0m\n",
			curenttime(philo->start), philo->id);
		philo->data->dead = 0;
		pthread_mutex_unlock(&philo->data->lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->lock);
	return (0);
}

long int	my_sleep(long int death_time, t_philo *philo, long int u_sec)
{
	while (u_sec > curenttime(philo->start))
	{
		usleep(1000);
		pthread_mutex_lock(&philo->data->lock);
		if (checkdeath(death_time, curenttime(philo->start), philo))
		{
			pthread_mutex_unlock(&philo->data->lock);
			return (-1);
		}
		//printf("curenttime = %ld ; usec = %ld\n", curenttime(philo->start), u_sec);
	}
	return (death_time);
}

long int	check_write(t_philo *philo, long int death_time, char *msg)
{
	pthread_mutex_lock(&philo->data->lock);
	if (checkdeath(death_time, curenttime(philo->start), philo))
		return (-1);
	pthread_mutex_lock(&philo->data->lock);
	printf("%ldms \033[90mphilo %d \033%s\033[0m\n",
		curenttime(philo->start), philo->id, msg);
	pthread_mutex_unlock(&philo->data->lock);
	return (death_time);
}
