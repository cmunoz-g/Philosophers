#include "philo.h"

void	clean(t_data *data)
{
	int i;

	i = 0;
	while (i < data->nbr_philos)
	{
		pthread_mutex_destroy(&(data->forks[i].fork_mutex));
		i++;
	}
	if (data->forks)
		free(data->forks);
	if (data->philos)
		free(data->philos);
	pthread_mutex_destroy(&(data->dead_mutex));
	pthread_mutex_destroy(&(data->write_mutex));
	pthread_mutex_destroy(&(data->meal_mutex));
	pthread_mutex_destroy(&(data->error_mutex));
}