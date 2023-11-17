/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 12:00:54 by kle-rest          #+#    #+#             */
/*   Updated: 2023/11/17 16:07:59 by kle-rest         ###   ########.fr       */
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

int	say(t_philo *philo, char *str)
{
	if (check_death(philo))
		return (0);
	pthread_mutex_lock(&philo->data->write);
	printf("%ld \033[90mphilo %d \033%s\033[0m\n", curenttime(philo->start_time), philo->id, str);
	pthread_mutex_unlock(&philo->data->write);
	return (1);
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
