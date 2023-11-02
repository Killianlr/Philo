/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 12:00:54 by kle-rest          #+#    #+#             */
/*   Updated: 2023/10/31 13:30:21 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

long	int	get_time(void)
{
	struct timeval start;

	gettimeofday(&start, NULL);
	return (start.tv_sec * 1000 + start.tv_usec / 1000);
}