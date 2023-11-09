/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 14:17:49 by kle-rest          #+#    #+#             */
/*   Updated: 2023/11/09 11:30:14 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_info(t_data *data)
{
	int	i;

	i = 0;
	printf("------PARAMS------\n");
	if (data->meal_nb > 0)
		printf("number of philo = %d, death time = %ldms, eat_time = %ldms, sleep time = %ldms meal number = %d\n",
		 data->philo_nb, data->death_time, data->eat_time, data->sleep_time, data->meal_nb);
	else
		printf("number of philo = %d, death time = %ldms, eat_time = %ldms, sleep time = %ld\n",
		data->philo_nb, data->death_time, data->eat_time, data->sleep_time);
}