#include "philo.h"

static int	init_mutex3(t_data *data)
{
	if (pthread_mutex_init(&data->write, NULL) != 0)
	{
		data->writeon = 1;
		return (0);
	}
	if (pthread_mutex_init(&data->death, NULL) != 0)
	{
		data->deathon = 1;
		return (0);
	}
	return (1);
}

static int	init_mutex_tab(pthread_mutex_t *mutex, int i)
{
	int	s;

	s = 0;
	while (s < i)
	{
		if (pthread_mutex_init(&mutex[s], NULL) != 0)
			return (s);
		s++;
	}
	return (s);
}

static int	init_mutex2(t_data *data, int i)
{
	int	mi;

	mi = 0;
	mi = init_mutex_tab(data->fork, i);
	if (mi != i)
	{
		while (--mi)
			pthread_mutex_destroy(&data->fork[mi]); 
		return (0);
	}
	mi = init_mutex_tab(data->philock, i);
	if (mi != i)
	{
		while (--mi)
			pthread_mutex_destroy(&data->philock[mi]);
		while (--i)
			pthread_mutex_destroy(&data->fork[i]);
		return (0);
	}
	return (1);
}

int	init_mutex(t_data *data)
{
	int	i;

	i = data->philo_nb;
	data->fork = malloc(sizeof(pthread_mutex_t) * data->philo_nb);
	if (!data->fork)
		return (0);
	data->philock = malloc(sizeof(pthread_mutex_t) * data->philo_nb);
	if (!data->philock)
		return (0);
	if (!init_mutex2(data, i))
		return (0);
	if (!init_mutex3(data))
		return (0);
	return (1);
}
