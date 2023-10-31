/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 13:23:09 by kle-rest          #+#    #+#             */
/*   Updated: 2023/10/27 14:43:27 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// int	ft_error_data(t_data *data)
// {
// 	printf("error malloc data\n");
// 	free(data);
// 	return (1);
// }

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