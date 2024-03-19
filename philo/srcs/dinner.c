#include "philo.h"

// revisar si usar pthread join o detach

void	create_threads(t_data *data)
{
	pthread_t		monitor;
	static int		i = 0;

	if (pthread_create(&monitor, NULL, monitoring, (void *) data))
		(clean(data), error("Could not create the monitoring thread"));
	while (i < data->nbr_philos)
	{
		if (pthread_create(&data->philos[i].thread_id, NULL, &dinner, (void *) &data->philos[i]))
			(clean(data), error("Could not create a philo thread"));
		i++;
	}
	if (pthread_join(monitor, NULL))
		(clean(data), error("Could not join the monitoring thread")); 
	i = 0;
	while (i < data->nbr_philos)
	{
		if (pthread_join(data->philos[i].thread_id, NULL)) 
			(clean(data), error("Could not join a philo thread"));
		i++;
	}
}

void	*dinner(void *pointer)
{
	t_philo	*philo;
	
	philo = (t_philo *)pointer;
	while (!check_end(philo) && !check_error(philo))
	{
		eat(philo);
		dream(philo);
		think(philo);
	}
	return (NULL);
}
