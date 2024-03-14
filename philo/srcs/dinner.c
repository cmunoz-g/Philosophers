#include "philo.h"

// revisar si usar pthread join o detach

void	create_threads(t_data *data)
{
	pthread_t		monitor;
	static size_t	i = 0;

	if (pthread_create(&monitor, NULL, monitoring, (void *) &data))
		error("Could not create the monitoring thread");
	while (i < data->nbr_philos)
	{
		if (pthread_create(&data->philos[i].thread_id, NULL, dinner, (void *) &data->philos[i]))
			error("Could not create a philo thread"); // revisar que pasa cuando por ejemplo falla la ultima.
		i++;
	}
	if (pthread_join(monitor, NULL))
		error("Could not join the monitoring thread"); 
	i = 0;
	while (i < data->nbr_philos)
	{
		if (pthread_join(data->philos[i].thread_id, NULL))
			error("Could not join a philo thread");
		i++;
	}
}

void	*dinner(void *philo)
{
	philo = (t_philo *)philo;
	while (!check_end(&philo))
	{
		eat(&philo);
		sleep(&philo);
		think(&philo);
	}
	return (NULL); // revisar si los threads nos obligan a que esta ft sea void * o si puede ser void
}