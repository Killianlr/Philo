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

int	checkdeath(long int death_time, long int curent_time)
{
	if (death_time < curent_time)
	{
		printf("someone is dead\n");
		return (1);
	}
	return (0);
}

void	*start_dinner(void *arg)
{
	t_philo	*philo;
	struct timeval	start;
	long	int	death_time;

	philo = (t_philo *)arg;
	gettimeofday(&start, NULL);
	death_time = philo->time_to_die;
	// while(philo->eat_count != philo->data->meal_nb)
	// {
		// locker(philo->l_fork);
	usleep(philo->data->sleep_time * 1000);
	if(checkdeath(death_time, curenttime(philo->start)) == 1)
		printf("break\n");// break ;
	pthread_mutex_lock(&philo->data->write);
	printf("%ldms philo %d has taken a fork\n", curenttime(philo->start), philo->id);
	pthread_mutex_unlock(&philo->data->write);
	// }
	return (NULL);
}