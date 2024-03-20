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
	pthread_mutex_destroy(&(data->dead_mutex));
	pthread_mutex_destroy(&(data->write_mutex));
	pthread_mutex_destroy(&(data->meal_mutex));
	pthread_mutex_destroy(&(data->error_mutex));
	if (data->forks)
		free(data->forks);
	if (data->philos)
		free(data->philos);
}

void	clean_mutex(t_data *data, int mutex_flag)
{
	if (mutex_flag == 1)
		pthread_mutex_destroy(&(data->dead_mutex));
	else if (mutex_flag == 2)
	{
		pthread_mutex_destroy(&(data->dead_mutex));
		pthread_mutex_destroy(&(data->meal_mutex));
	}
	else if (mutex_flag == 3)
	{
		pthread_mutex_destroy(&(data->dead_mutex));
		pthread_mutex_destroy(&(data->meal_mutex));
		pthread_mutex_destroy(&(data->write_mutex));
	}
	if (data->philos)
		free(data->philos);
	if (data->forks)
		free(data->forks);
}
void	clean_fork_mutex(t_data *data, int fork_mutex_flag)
{
	int i;

	i = 0;
	while (i < fork_mutex_flag)
	{
		pthread_mutex_destroy(&(data->forks[i].fork_mutex));
		i++;
	}
	pthread_mutex_destroy(&(data->dead_mutex));
	pthread_mutex_destroy(&(data->meal_mutex));
	pthread_mutex_destroy(&(data->write_mutex));
	pthread_mutex_destroy(&(data->error_mutex));
	if (data->philos)
		free(data->philos);
	if (data->forks)
		free(data->forks);
}