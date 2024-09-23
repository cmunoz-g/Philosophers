/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmunoz-g <cmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 11:39:57 by cmunoz-g          #+#    #+#             */
/*   Updated: 2024/04/23 09:14:29 by cmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * check_error
 *
 * Checks if there has been an error flagged within the shared data among 
 * philosophers.
 * This function locks the error mutex, checks the error flag, 
 * and then unlocks the mutex.
 *
 * @param philo	Pointer to the philosopher structure.
 * @return		Returns 1 if an error is flagged, 0 otherwise.
 */

int	check_error(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->error_mutex));
	if (philo->data->error_flag == true)
	{
		pthread_mutex_unlock(&(philo->data->error_mutex));
		return (1);
	}
	pthread_mutex_unlock(&(philo->data->error_mutex));
	return (0);
}

/**
 * check_end
 *
 * Checks if the simulation should end based on the death of a philosopher.
 * This function locks the death mutex, checks the death flag,
 * and, if set, performs a brief sleep before unlocking 
 * the mutex and returning.
 *
 * @param philo	Pointer to the philosopher structure.
 * @return		Returns 1 if a philosopher is dead, 0 otherwise.
 */

int	check_end(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->dead_mutex));
	if (philo->data->dead)
	{
		precise_usleep(1, philo->data);
		pthread_mutex_unlock(&(philo->data->dead_mutex));
		return (1);
	}
	pthread_mutex_unlock(&(philo->data->dead_mutex));
	return (0);
}

void	check_nbr(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '-')
			error("Negative number");
		else if (str[i] < 48 || str[i] > 57)
			error("Wrong input");
		i++;
	}
}

void	check_input(int argc, char **argv, t_data *data)
{
	size_t	i;

	i = 1;
	while (argv[i])
		check_nbr(argv[i++]);
	data->nbr_philos = ft_atoi(argv[1]);
	if (data->nbr_philos <= 0)
		error("Not enough philosophers!");
	data->time_to_die = ft_atoi(argv[2]);
	if (data->time_to_die <= 0)
		error("Not enough time to die");
	data->time_to_eat = ft_atoi(argv[3]);
	if (data->time_to_eat <= 0)
		error("Not enough time to eat");
	data->time_to_sleep = ft_atoi(argv[4]);
	if (data->time_to_sleep <= 0)
		error("Not enough time to sleep");
	if (argc == 6)
		data->nbr_max_meals = ft_atoi(argv[5]);
	data->argc = argc;
}

int	check_full(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_philos)
	{
		if (data->philos[i].full == false)
			return (1);
		i++;
	}
	return (0);
}
