/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmunoz-g <cmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 12:05:46 by cmunoz-g          #+#    #+#             */
/*   Updated: 2024/04/23 09:13:38 by cmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * get_time
 *
 * Retrieves the current time in milliseconds. It uses gettimeofday to fetch 
 * the current time and converts it into milliseconds. If gettimeofday fails,
 * it sets an error flag in the shared data structure and logs the failure.
 *
 * @param data Pointer to the shared data struct with error handling flags.
 * @return Returns the current time in milliseconds. 
 */

int	get_time(t_data *data)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
	{
		pthread_mutex_lock(&(data->error_mutex));
		data->error_flag = true;
		pthread_mutex_unlock(&(data->error_mutex));
		error("gettimeofday() failed");
	}
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

/**
 * precise_usleep
 *
 * Pauses the execution for a specified number of milliseconds. This function
 * uses a busy-wait loop to periodically check the elapsed time, ensuring
 * that the sleep duration is precise.
 * It also checks for errors in usleep and sets an error flag if usleep fails.
 *
 * @param ms	The number of milliseconds to sleep.
 * @param data	Pointer to the shared data structure for error handling.
 */

void	precise_usleep(int ms, t_data *data)
{
	int	start;

	start = get_time(data);
	while (get_time(data) - start < ms)
	{
		if (usleep(500))
		{
			pthread_mutex_lock(&(data->error_mutex));
			data->error_flag = true;
			pthread_mutex_unlock(&(data->error_mutex));
			error("usleep() failed");
		}
	}
}
