#include "philo.h"

int	dead_status(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_philos)
	{
		pthread_mutex_lock(&(data->meal_mutex));
		if ((get_time(data->start) - data->philos[i].last_meal) >= data->time_to_die)
		{			
			write_message((i + 1), "died", data); // si este mensaje sale antes de algun otro, meter aqui un pequeno delay de tiempo?
			pthread_mutex_lock(&(data->dead_mutex));
			data->dead = true;
			pthread_mutex_unlock(&(data->meal_mutex));
			pthread_mutex_unlock(&(data->dead_mutex));
			return (0);
		} 
		pthread_mutex_unlock(&(data->meal_mutex));
		i++;
	}
	return (1);
}

int	full_status(t_data *data) 
{
	int	i;

	i = 0;
	pthread_mutex_lock(&(data->meal_mutex));
	while (i < data->nbr_philos)
	{
		if (data->philos[i].num_meals == data->nbr_max_meals)
			data->finished++;
		i++;
	}
	if (data->finished == data->nbr_philos)
	{
		pthread_mutex_lock(&(data->dead_mutex));
		data->dead = true;
		pthread_mutex_unlock(&(data->dead_mutex));
		pthread_mutex_unlock(&(data->meal_mutex));
		return (0);
	}
	pthread_mutex_unlock(&(data->meal_mutex));
	return (1);
}

void	*monitoring(void *data)
{
	t_data	*monitor_data;

	monitor_data = (t_data *)data;
	//printf("%d\n",monitor_data->argc);
	while (1)
	{
		if (!dead_status(monitor_data))
			break ;
		if (monitor_data->argc == 6)
		{
			if (!full_status(monitor_data))
				break ;
		}
	}
	return (NULL);
}