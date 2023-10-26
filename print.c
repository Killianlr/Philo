/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 14:17:49 by kle-rest          #+#    #+#             */
/*   Updated: 2023/10/26 14:27:27 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print(t_data *data)
{
	printf("number of philo = %d\n", data->philo_nb);
	printf("death time = %ldms\n", data->death_time);
	printf("eat_time = %ldms\n", data->eat_time);
	printf("sleep time = %ldms\n", data->sleep_time);
	if (data->meal_nb)
		printf("meal number %d\n", data->meal_nb);


	printf("------START------\n");
}