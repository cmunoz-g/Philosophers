/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmunoz-g <cmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 11:41:57 by cmunoz-g          #+#    #+#             */
/*   Updated: 2024/04/23 09:14:12 by cmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * create_threads
 *
 * It creates threads for each philosopher to simulate their activities and 
 * one monitor thread to oversee the state of the simulation. If thread 
 * creation fails at any point, it cleans up and reports an error. 
 * After all threads are created, it joins them back to ensure all
 * threads have completed before the program exits.
 *
 * @param data	Pointer to the shared data struct that holds philosopher info.
 */

void	create_threads(t_data *data)
{
	pthread_t		monitor;
	static int		i = 0;

	if (pthread_create(&monitor, NULL, monitoring, (void *) data))
		(clean(data), error("Could not create the monitoring thread"));
	while (i < data->nbr_philos)
	{
		if (pthread_create(&data->philos[i].thread_id, NULL,
				&dinner, (void *) &data->philos[i]))
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

/**
 * dinner
 *
 * Represents the lifecycle of a philosopher involving eating, sleeping, 
 * and thinking. This function is the main activity for each philosopher 
 * thread, repeatedly executing the eat, dream (sleep), and think routines 
 * as long as no termination conditions are met (death or error flags).
 * The loop continues until either a philosopher dies or an
 * error occurs.
 *
 * @param pointer	A void pointer to the philosopher structure.
 * @return			Returns NULL upon completion of the loop.
 */

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
