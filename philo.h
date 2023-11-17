/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 11:37:17 by kle-rest          #+#    #+#             */
/*   Updated: 2023/11/17 14:21:30 by kle-rest         ###   ########.fr       */
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

struct	s_philo;

typedef struct s_philo
{
	pthread_t		th;
	int				id;
	int				eat_count;
	int				*is_dead;
	long int		time_to_die;
	long int		start_time;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	philock;
	struct s_data	*data;
	struct s_philo	*next;
}			t_philo;

typedef struct s_data
{
	struct s_philo	*philo;
	int				philo_nb;
	int				meal_nb;
	int				is_dead;
	long int		death_time;
	long int		eat_time;
	long int		sleep_time;
	long int		start_time;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*philock;
	pthread_mutex_t	death;
	pthread_mutex_t	write;
	pthread_t		check;
}			t_data;


int			check_params(int ac, char **av);
int			ft_is_number(char **av);
int			ft_check_int(int ac, char **av);
long int	ft_atoi_long(const char *nptr);
int			init_data(t_data *data, int ac, char **av);
void		print_info(t_data *data);
t_philo		*create_philo(t_data *data, t_philo *philo);
void		*start_dinner(void *arg);
int			init_mutex(t_data *data);
int			free_mutex(t_data *data, char *msg);
int			free_data(t_data *data, char *msg);
int			free_philo(t_data *data, t_philo *philo, char *msg);
int			error_thread(t_data *data, t_philo *philo, char *msg);
int			init_thread(t_data *data);
long int	get_time(void);
long int	check_write(t_philo *philo, long int death_time, char *msg);
//long int	my_sleep(long int death_time, t_philo *philo, long int u_sec);
//int			checkdeath(long int death_time, long int curent_time,
//				t_philo *philo);
long int	curenttime(long int start);
void		ft_end(t_data *data, t_philo *philo);
int			check_death(t_philo *philo);
int			say(t_philo *philo, char *str);
int			my_sleep(t_philo *philo, long int sleep_time);



#endif