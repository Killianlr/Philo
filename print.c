/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 14:17:49 by kle-rest          #+#    #+#             */
/*   Updated: 2023/11/07 09:46:08 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_info(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	printf("------DATA------\n");
	printf("number of philo = %d, death time = %ldms, eat_time = %ldms, sleep time = %ldms\n", data->philo_nb, data->death_time, data->eat_time, data->sleep_time);
	if (data->meal_nb)
		printf("meal number %d\n", data->meal_nb);
	printf("\n");

	(void)philo;
// 	printf("------PHILO------\n");
// 	while (philo->next)
// 	{
// 		printf("id = %d, eat_count = %d, status = %d, time_to_die = %ldms\n", philo->id, philo->eat_count, philo->status, philo->time_to_die);
// 		philo = philo->next;
// 		i++;
// 	}
// 	printf("id = %d, eat_count = %d, status = %d, time_to_die = %ldms\n", philo->id, philo->eat_count, philo->status, philo->time_to_die);

}