/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 14:09:57 by kle-rest          #+#    #+#             */
/*   Updated: 2023/11/17 16:08:51 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *philo)
{
	say(philo, "[92mis eating");
	pthread_mutex_lock(&philo->philock);
	philo->eat_count++;
	philo->time_to_die = curenttime(philo->data->start_time) + philo->data->death_time;
	pthread_mutex_unlock(&philo->philock);
	my_sleep(philo, philo->data->eat_time);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	sleeping(t_philo *philo)
{
	say(philo, "[94mis sleeping");
	my_sleep(philo, philo->data->sleep_time);
}

void	*start_dinner(void *arg)
{
	t_philo		*philo;
	
	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->philock);
	while (philo->eat_count != philo->data->meal_nb && !check_death(philo))
	{
		pthread_mutex_unlock(&philo->philock);
		pthread_mutex_lock(philo->l_fork);
	 	pthread_mutex_lock(philo->r_fork);
		say(philo, "[93mhas taken a fork");
		say(philo, "[93mhas taken a fork");
		eating(philo);
		sleeping(philo);
		say(philo, "[95mis thinking");
		pthread_mutex_lock(&philo->philock);
	}
	pthread_mutex_unlock(&philo->philock);
	return (NULL);
}