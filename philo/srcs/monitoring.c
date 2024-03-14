#include "philo.h"

int	dead_status(t_data *data) // incorporar la ft de tiempo que compruebe si debemos cambiar el estado a muerto, en principio no necesito mutexes, //llamo al mensaje desde aqui?

int	full_status(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->nbr_philos)
	{
		if (data->philos[i].num_meals != data->nbr_max_meals)
			return (1);
		i++;
	}
	data->full = true;
	return (0);
}

void	*monitoring(void *data)
{
	data = (t_data *)data;
	while (1)
	{
		if (!dead_status(data))
			break ;
		if (data->max_meals_arg)
			if (!full_status(data))
				break ;
	}
	return (NULL);
}