#include "philo.h"

void	create_threads(t_data *data)
{
	pthread_t		thread; // cambiar nombre
	static size_t	i = 0;

	while (i < data->nbr_philos)
	{
		if (pthread_create())
			error("Could not create a thread"); // lo mismo, revisar que pasa cuando por ejemplo falla la ultima.

	}
}
// crear threads
// philo rutina romper cuando flag de dead es true o cuando llegan al max de comidas (todos los bool de full estan llenso)