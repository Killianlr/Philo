/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 14:09:57 by kle-rest          #+#    #+#             */
/*   Updated: 2023/11/09 12:11:51 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// int	take_fork(t_philo *philo, long int death_time)
// {
// 	pthread_mutex_lock(&philo->data->lock);
	
// 	pthread_mutex_lock(philo->l_fork);
// 	pthread_mutex_lock(philo->r_fork);
// 	check_write(philo, death_time, "[93mhas taken a fork");
// 	check_write(philo, death_time, "[93mhas taken a fork");
// 	return (0);
// }

// long int	eating(t_philo *philo, long int death_time)
// {
// 	death_time = check_write(philo, death_time, "[92mis eating");
// 	philo->eat_count ++;
// 	death_time = curenttime(philo->start) + philo->time_to_die;
// 	death_time = my_sleep(death_time, philo, curenttime(philo->start) + philo->data->eat_time);
// 	death_time = curenttime(philo->start) + philo->time_to_die;
// 	pthread_mutex_unlock(philo->r_fork);
// 	pthread_mutex_unlock(philo->l_fork);
// 	return (death_time);
// }

// long int	sleeping(t_philo *philo, long int death_time)
// {
// 	death_time = check_write(philo, death_time, "[94mis sleeping");
// 	death_time = my_sleep(death_time, philo, curenttime(philo->start_time) + philo->data->sleep_time);
// 	return (death_time);
// }

// long int	thinking(t_philo *philo, long int death_time)
// {
// 	death_time = check_write(philo, death_time, "[95mis thinking");
// 	return (death_time);
// }

// void	*start_dinner(void *arg)
// {
// 	t_philo			*philo;
// 	struct timeval	start;
// 	long int		death_time;

// 	philo = (t_philo *)arg;
// 	gettimeofday(&start, NULL);
// 	death_time = philo->time_to_die;
// 	if (philo->id % 2 == 0)
// 		usleep(1);
// 	while (philo->eat_count != philo->data->meal_nb && philo->data->dead)
// 	{
// 		if (take_fork(philo, death_time))
// 			break ;
// 		if (philo->data->dead)
// 			death_time = eating(philo, death_time);
// 		if (philo->data->dead)
// 			death_time = sleeping(philo, death_time);
// 		if (philo->data->dead)
// 			death_time = thinking(philo, death_time);
// 	}
// 	pthread_mutex_unlock(philo->r_fork);
// 	pthread_mutex_unlock(philo->l_fork);
// 	return (NULL);
// }


///////////////////////////////////////////////////////////////////////////////////////////////////

int	my_sleep(t_philo *philo, long int sleep_time)
{
	long int	wake_up;

	if (check_death(philo))
		return (0);
	wake_up = curenttime(philo->start_time) + sleep_time;
	while (wake_up > curenttime(philo->start_time))
	{
		usleep(10);
		// if (check_death(philo))
		// 	return (0);
	}
	return (1);
}

int	say(t_philo *philo, char *str)
{
	if (check_death(philo))
		return (0);
	//pthread_mutex_lock(&philo->data->write);
	printf("%ld philo %d %s\n", curenttime(philo->start_time), philo->id, str);
	//pthread_mutex_unlock(&philo->data->write);
	return (1);
}

void	eating(t_philo *philo)
{
	say(philo, "is eating");
	//pthread_mutex_lock(&philo->philock);
	philo->eat_count++;
	philo->time_to_die = curenttime(philo->data->start_time) + philo->data->death_time;
	//pthread_mutex_unlock(&philo->philock);
	my_sleep(philo, philo->data->eat_time);
	//pthread_mutex_unlock(philo->l_fork);
	//pthread_mutex_unlock(philo->r_fork);
}

void	sleeping(t_philo *philo)
{
	say(philo, "is sleeping");
	my_sleep(philo, philo->data->sleep_time);
}

void	*start_dinner(void *arg)
{
	t_philo		*philo;
	
	philo = (t_philo *)arg;
	//pthread_mutex_lock(&philo->philock);
	while (philo->eat_count != philo->data->meal_nb && !check_death(philo))
	{
	//	pthread_mutex_unlock(&philo->philock);
	//	pthread_mutex_lock(philo->l_fork);
	 //	pthread_mutex_lock(philo->r_fork);
		say(philo, "has taken a fork");
		say(philo, "has taken a fork");
		eating(philo);
		sleeping(philo);
		say(philo, "is thinking");
	//	pthread_mutex_lock(&philo->philock);
	}
	//pthread_mutex_unlock(&philo->philock);
	return (NULL);
}