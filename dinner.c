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

void	begin(t_philo *philo)
{
	philo->data->dead = 1;
}

int	start_dinner(t_philo *philo)
{
	begin(philo);
	if (philo->data->dead == 1)
		return (0);
	return (1);
}