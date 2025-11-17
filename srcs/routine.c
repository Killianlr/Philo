/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 14:09:57 by kle-rest          #+#    #+#             */
/*   Updated: 2023/11/21 18:20:48 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	say(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->data->write);
	if (check_death(philo))
	{
		pthread_mutex_unlock(&philo->data->write);
		return (0);
	}
	printf("%ld \033[90mphilo %d \033%s\033[0m\n",
		curenttime(philo->start_time), philo->id, str);
	pthread_mutex_unlock(&philo->data->write);
	return (1);
}

void	eating(t_philo *philo)
{
	say(philo, "[92mis eating");
	pthread_mutex_lock(&philo->philock);
	philo->eat_count++;
	philo->time_to_die = curenttime(philo->data->start_time)
		+ philo->data->death_time;
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

void	*routine_dinner(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->philock);
	while (!check_death(philo))
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

void	*routine_death(void *arg)
{
	t_philo	*philo;
	int		philo_full;

	philo = (t_philo *)arg;
	philo_full = 0;
	while (philo && !check_death(philo))
	{
		pthread_mutex_lock(&philo->philock);
		if (philo->id == 1)
			philo_full = 0;
		if (philo->eat_count == philo->data->meal_nb)
			philo_full++;
		if ((philo->time_to_die < curenttime(philo->start_time))
			|| philo_full == philo->data->philo_nb)
			end(philo, philo_full);
		pthread_mutex_unlock(&philo->philock);
		philo = philo->next;
	}
	return (NULL);
}
