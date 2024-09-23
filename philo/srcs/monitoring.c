/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmunoz-g <cmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 12:05:12 by cmunoz-g          #+#    #+#             */
/*   Updated: 2024/04/23 09:13:45 by cmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * dead_status
 *
 * Checks for any philosopher who has died due to not eating within the 
 * time-to-die limit. This function iterates over all philosophers, checking 
 * if the time since their last meal exceeds the death threshold. 
 * If a philosopher has died, it sets the simulation's dead flag and logs it.
 *
 * @param data	Pointer to the shared data struct with the simulation data.
 * @return		Returns 0 if a philosopher has died, 1 otherwise.
 */

int	dead_status(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_philos)
	{
		pthread_mutex_lock(&(data->meal_mutex));
		if ((get_time(data) - data->philos[i].last_meal) >= data->time_to_die)
		{
			write_msg((i + 1), "died\t\t   "EM_DEAD, data, 0);
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

/**
 * full_status
 *
 * Evaluates whether all philosophers have eaten the required number of meals.
 * If all philosophers have reached the specified number of meals, 
 * the simulation's dead flag is set to end the simulation.
 *
 * @param data Pointer to the shared data struct with all simulation data.
 * @return Returns 0 if all philosophers are full, 1 otherwise.
 */

int	full_status(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&(data->meal_mutex));
	while (i < data->nbr_philos)
	{
		if (data->philos[i].num_meals == data->nbr_max_meals)
			data->philos[i].full = true;
		i++;
	}
	if (!check_full(data))
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

/**
 * monitoring
 *
 * Continuously monitors the status of all philosophers, checking for 
 * any deaths or if all philosophers are fully sated. The loop breaks 
 * if a death occurs or if all philosophers are full, depending on 
 * the simulation's configuration.
 *
 * @param data Void pointer to the shared data struct used for monitoring.
 * @return Returns NULL after ending the monitoring loop.
 */

void	*monitoring(void *data)
{
	t_data	*monitor_data;

	monitor_data = (t_data *)data;
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
