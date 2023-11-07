/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 13:23:09 by kle-rest          #+#    #+#             */
/*   Updated: 2023/11/07 09:39:01 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int    free_mutex(t_data *data, char *msg)
{
    int i;

    i = 0;
    while (&data->fork[i])
    {
        pthread_mutex_destroy(&data->fork[i]);
        i++;
    }
    pthread_mutex_destroy(&data->lock);
    pthread_mutex_destroy(&data->write);
    free(data);
    printf("%s\n", msg);
    return (1);
}

int    free_data(t_data *data, char *msg)
{
    printf("%s\n", msg);
	free(data);
    return (1);
}

int    free_philo(t_data *data, t_philo *philo, char *msg)
{
    t_philo *tmp;

    tmp = philo;
    printf("%s\n", msg);
    while (philo)
    {
       tmp = philo;
       philo = philo->next; 
       free(tmp);
    }
    free(data);
    return (1);
}

// int	ft_error_thread(t_data *data)
// {
// 	int	i;

// 	i = 0;
// 	printf("error thread\n");
// 	if (data->philo)
// 		free(data->philo);
// 	// while (i < data->philo_nb)
// 	// {
// 	// 	free(data->tid[i]);
// 	// 	i++;
// 	// }
// 	free(data->tid);
// 	free(data);
// 	return (1);
// }
