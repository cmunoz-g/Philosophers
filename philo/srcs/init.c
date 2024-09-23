/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmunoz-g <cmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 11:42:52 by cmunoz-g          #+#    #+#             */
/*   Updated: 2024/04/23 09:13:58 by cmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * init_forks
 *
 * Initializes mutexes for each fork used by philosophers. It sets an ID for 
 * each fork and attempts to initialize a mutex for each. If initialization 
 * fails, it cleans up previously initialized mutexes and reports an error.
 *
 * @param data	Pointer to the shared data structure containing fork info.
 */

void	init_forks(t_data *data)
{
	static int	i = 0;

	while (i < data->nbr_philos)
	{
		data->forks[i].fork_id = i + 1;
		if (pthread_mutex_init(&(data->forks[i].fork_mutex), NULL))
		{
			clean_fork_mutex(data, i);
			error("Could not initialize a fork mutex");
		}
		i++;
	}
}

/**
 * init_philos
 *
 * Initializes each philosopher's data structure. Sets their unique ID,
 * starting meal count, and full status. Assigns left and right forks 
 * considering the circular arrangement at the table, linking the 
 * first and last philosopher's forks as necessary.
 *
 * @param data	Pointer to the shared data struct where philosophers are stored.
 */

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

/**
 * init_data
 *
 * Allocates memory and initializes the mutexes and data structures 
 * for managing philosophers and their forks. Sets up the initial 
 * state and times, and calls other initialization functions.
 *
 * @param data	Pointer to the shared data structure to be initialized.
 */

void	init_data(t_data *data)
{
	data->dead = false;
	data->error_flag = false;
	data->philos = (t_philo *)malloc(sizeof(t_philo) * data->nbr_philos);
	if (!data->philos)
		error("Memory issues while allocating philo structures");
	data->forks = (t_fork *)malloc(sizeof(t_fork) * data->nbr_philos);
	if (!data->forks)
		error("Memory issues while allocating fork structures");
	if (pthread_mutex_init(&data->dead_mutex, NULL))
		(clean_mutex(data, 0), error("Could not initialize dead mutex"));
	if (pthread_mutex_init(&data->meal_mutex, NULL))
		(clean_mutex(data, 1), error("Could not initialize meal mutex"));
	if (pthread_mutex_init(&data->write_mutex, NULL))
		(clean_mutex(data, 2), error("Could not initialize write mutex"));
	if (pthread_mutex_init(&data->error_mutex, NULL))
		(clean_mutex(data, 3), error("Could not initialize error mutex"));
	data->start = get_time(data);
	init_forks(data);
	init_philos(data);
}
