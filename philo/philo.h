/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 11:37:17 by kle-rest          #+#    #+#             */
/*   Updated: 2023/11/23 12:15:34 by kle-rest         ###   ########.fr       */
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
	int				writeon;
	int				deathon;
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

int			init_mutex(t_data *data);
int			check_params(int ac, char **av);
int			init_thread(t_data *data, t_philo *philo);
void		ft_free_end(t_data *data, t_philo *philo);
int			init_data(t_data *data, int ac, char **av);
t_philo		*create_philo(t_data *data, t_philo *philo);

int			free_mutex(t_data *data, char *msg);
int			free_data(t_data *data, char *msg);
int			free_philo(t_data *data, t_philo *philo, char *msg);
int			error_thread(t_data *data, t_philo *philo, char *msg);

long int	get_time(void);
long int	curenttime(long int start);
int			check_death(t_philo *philo);
void		end(t_philo *philo, int philo_full);
int			my_sleep(t_philo *philo, long int sleep_time);

int			thread_join(t_data *data);
int			init_thread(t_data *data, t_philo *philo);

void		*routine_death(void *arg);
void		*routine_dinner(void *arg);

long int	ft_atoi_long(const char *nptr);

#endif