/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 11:37:17 by kle-rest          #+#    #+#             */
/*   Updated: 2023/10/26 14:18:48 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdint.h>

typedef struct s_data
{
	struct t_philo			*philo;
	pthread_t		*tid;
	int				philo_nb;
	int				meal_nb;
	int				dead;
	int				finished;
	uint64_t		death_time;
	uint64_t		eat_time;
	uint64_t		sleep_time;
	uint64_t		start_time;
	pthread_mutex_t	*fork;
	pthread_mutex_t	lock;
	pthread_mutex_t	write;
}			t_data;

typedef struct s_philo
{
	t_data			*data;
	pthread_t		t1;
	int				id;
	int				eat_count;
	int				status;
	int				eating;
	uint64_t		time_to_die;
	pthread_mutex_t	lock;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
}			t_philo;

int	ft_is_number(char **av);
int	ft_check_int(int ac, char **av);
long	int	ft_atoi_long(const char *nptr);
void	set_data(t_data *data, int ac, char **av);
void	print(t_data *data);

#endif