/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 11:37:17 by kle-rest          #+#    #+#             */
/*   Updated: 2023/10/31 14:26:42 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdint.h>
# include <time.h>
# include <sys/time.h>
# include <unistd.h>

struct s_philo;

typedef struct s_data
{
	struct s_philo	*philo;
	pthread_t		*tid;
	int				philo_nb;
	int				meal_nb;
	int				dead;
	int				finished;
	long int		death_time;
	long int		eat_time;
	long int		sleep_time;
	long int		start_time;
	pthread_mutex_t	*fork;
	pthread_mutex_t	lock;
	pthread_mutex_t	write;
}			t_data;

typedef struct s_philo
{
	struct s_data	*data;
	pthread_t		t1;
	int				id;
	int				eat_count;
	int				status;
	int				eating;
	long int		time_to_die;
	pthread_mutex_t	lock;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	struct s_philo	*next;
}			t_philo;

int	ft_is_number(char **av);
int	ft_check_int(int ac, char **av);
long	int	ft_atoi_long(const char *nptr);
void	set_data(t_data *data, int ac, char **av);
void	print_info(t_data *data, t_philo *philo);
void	gettime();
t_philo	*create_philo(t_data *data, t_philo *philo);
int		start_dinner(t_philo *philo);
int		init_mutex(t_data *data);



#endif