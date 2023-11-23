/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 12:00:54 by kle-rest          #+#    #+#             */
/*   Updated: 2023/11/23 12:03:24 by kle-rest         ###   ########.fr       */
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

int	my_sleep(t_philo *philo, long int sleep_time)
{
	long int	wake_up;

	if (check_death(philo))
		return (0);
	wake_up = curenttime(philo->start_time) + sleep_time;
	while (wake_up > curenttime(philo->start_time))
	{
		usleep(1000);
		if (check_death(philo))
			return (0);
	}
	return (1);
}

void	end(t_philo *philo, int philo_full)
{
	pthread_mutex_lock(&philo->data->death);
	*philo->is_dead = 1;
	pthread_mutex_unlock(&philo->data->death);
	if (philo_full != philo->data->philo_nb)
	{
		pthread_mutex_lock(&philo->data->write);
		printf("%ld \033[90mphilo %d \033[91mdied\033[0m\n",
			curenttime(philo->start_time), philo->id);
		pthread_mutex_unlock(&philo->data->write);
	}
}

int	check_death(t_philo *philo)
{
	int	dying;

	pthread_mutex_lock(&philo->data->death);
	dying = *philo->is_dead;
	pthread_mutex_unlock(&philo->data->death);
	return (dying);
}
