#include "philo.h"

void	init_forks(t_data *data)
{
	static int	i = 0;

	while (i < data->nbr_philos)
	{
		data->forks[i].fork_id = i + 1;
		if (pthread_mutex_init(&(data->forks[i].fork_mutex), NULL)) // revisar , si esto falla deberia destruirlos antes de salir con exit?
			error("Could not initialize a fork mutex");
		i++;
	}
}

void	init_philos(t_data *data)
{
	static int	i = 0;

	while (i < data->nbr_philos)
	{
		data->philos[i].philo_id = i + 1;
		data->philos[i].num_meals = 0;
		data->philos[i].full = false;
		data->philos[i].last_meal = data->start;
		data->philos[i].right_fork = &data->forks[i];
		if (i == 0)
			data->philos[i].left_fork = &data->forks[data->nbr_philos - 1];
		else
			data->philos[i].left_fork = &data->forks[i - 1];
		data->philos[i].data = data;
		i++;
	}
}

void	init_data(t_data *data)
{
	data->dead = false;
	data->start = get_time();
	data->philos = (t_philo *)malloc(sizeof(t_philo) * data->nbr_philos);
	if (!data->philos)
		error("Memory issues while allocating philo structures");
	data->forks = (t_fork *)malloc(sizeof(t_fork) * data->nbr_philos);
	if (!data->forks)
		error("Memory issues while allocating fork structures");
	if (pthread_mutex_init(&data->dead_mutex, NULL))
		error("Could not initialize dead mutex");
	if (pthread_mutex_init(&data->meal_mutex, NULL))
	 	error("Could not initialize meal mutex");
	if (pthread_mutex_init(&data->write_mutex, NULL))
		error("Could not initialize write mutex");
	init_forks(data);
	init_philos(data);
}
