/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 14:09:57 by kle-rest          #+#    #+#             */
/*   Updated: 2023/10/31 14:19:50 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"


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
		printf("%ldms \033[90mphilo %d \033[91mdied\033[0m\n", curenttime(philo->start), philo->id);
		philo->data->dead = 0;
		pthread_mutex_unlock(&philo->data->lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->lock);
	return (0);
}

long int write_trhead(t_philo *philo, long int death_time, char *msg)
{
	pthread_mutex_lock(&philo->data->write);
	pthread_mutex_lock(&philo->data->lock);
	if (checkdeath(death_time, curenttime(philo->start), philo))
	{
		pthread_mutex_unlock(&philo->data->write);
		return (-1);
	}
	printf("%ldms \033[90mphilo %d \033%s\033[0m\n", curenttime(philo->start), philo->id, msg);
	pthread_mutex_unlock(&philo->data->write);
	return (death_time);
}

int	take_fork(t_philo *philo, long int death_time)
{
	pthread_mutex_lock(philo->l_fork);
	pthread_mutex_lock(philo->r_fork);
	write_trhead(philo, death_time, "[93mhas taken a fork");
	write_trhead(philo, death_time, "[93mhas taken a fork");
	return (0);
}



long int	eating(t_philo *philo, long int death_time)
{
	death_time = write_trhead(philo, death_time, "[92mis eating");
	philo->eat_count ++;
	usleep(philo->data->eat_time * 1000);
	death_time = curenttime(philo->start) + philo->time_to_die;
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	return (death_time);
}

long int	sleeping(t_philo *philo, long int death_time)
{
	death_time = write_trhead(philo, death_time, "[94mis sleeping");
	usleep(philo->data->sleep_time * 1000);
	return (death_time);
}

long int	thinking(t_philo *philo, long int death_time)
{
	death_time = write_trhead(philo, death_time, "[91mis thinking");
	return (death_time);
}

void	*start_dinner(void *arg)
{
	t_philo	*philo;
	struct timeval	start;
	long	int	death_time;

	philo = (t_philo *)arg;
	gettimeofday(&start, NULL);
	death_time = philo->time_to_die;
	if (philo->id % 2 == 0)
		usleep(100);
	while (philo->eat_count != philo->data->meal_nb && philo->data->dead)
	{
		if (take_fork(philo, death_time))
			break ;
		if (philo->data->dead)
			death_time = eating(philo, death_time);
		if (philo->data->dead)
			death_time = sleeping(philo, death_time);
		if (philo->data->dead)
			death_time = thinking(philo, death_time);
	}
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	return (NULL);
}