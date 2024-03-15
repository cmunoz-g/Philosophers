#include "philo.h"

void	clean(t_data *data)
{
	static int i = 0;

	while (i < data->nbr_philos)
	{
		pthread_mutex_destroy(&(data->forks[i].fork_mutex));
		i++;
	}
	free(data->forks);
	free(data->philos);
	pthread_mutex_destroy(&(data->dead_mutex));
	pthread_mutex_destroy(&(data->write_mutex));
	pthread_mutex_destroy(&(data->meal_mutex));
}