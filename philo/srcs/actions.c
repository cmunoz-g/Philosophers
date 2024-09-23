/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmunoz-g <cmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 11:34:10 by cmunoz-g          #+#    #+#             */
/*   Updated: 2024/04/23 09:14:49 by cmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	think(t_philo *philo)
{
	write_msg(philo->philo_id, "is thinking\t   "EM_THINK, philo->data, 0);
}

/**
 * eat
 *
 * Determines the order in which a philosopher picks up their forks based on 
 * their ID to avoid deadlock. If the philosopher's ID is odd, they pick up 
 * the left fork first, otherwise the right fork first.
 * It then calls eat_aux to handle the actual eating logic.
 *
 * @param philo	Pointer to the philosopher struct for which to simulate eating.
 */

void	eat(t_philo *philo)
{
	t_fork	*first;
	t_fork	*second;

	if (philo->philo_id % 2)
	{
		first = philo->left_fork;
		second = philo->right_fork;
	}
	else
	{
		first = philo->right_fork;
		second = philo->left_fork;
	}
	eat_aux(philo, first, second);
}

/**
 * eat_aux
 *
 * Handles the detailed actions involved in a philosopher eating. 
 * This includes taking forks, logging the action, updating the time 
 * of the last meal, and the total number of meals eaten.
 * Manages mutex locks to ensure that each philosopher can only eat 
 * when they have both forks.
 *
 * @param philo		Pointer to the philosopher structure.
 * @param first		Pointer to the first fork to be picked up.
 * @param second	Pointer to the second fork to be picked up.
 */

void	eat_aux(t_philo *philo, t_fork *first, t_fork *second)
{
	pthread_mutex_lock(&first->fork_mutex);
	write_msg(philo->philo_id, "has taken fork", philo->data, first->fork_id);
	if (philo->data->nbr_philos == 1)
	{
		precise_usleep(philo->data->time_to_die, philo->data);
		pthread_mutex_unlock(&first->fork_mutex);
		return ;
	}
	pthread_mutex_lock(&second->fork_mutex);
	write_msg(philo->philo_id, "has taken fork", philo->data, second->fork_id);
	write_msg(philo->philo_id, "is eating\t   "EM_EAT, philo->data, 0);
	pthread_mutex_lock(&(philo->data->meal_mutex));
	philo->last_meal = get_time(philo->data);
	philo->num_meals++;
	pthread_mutex_unlock(&(philo->data->meal_mutex));
	precise_usleep(philo->data->time_to_eat, philo->data);
	pthread_mutex_unlock(&first->fork_mutex);
	pthread_mutex_unlock(&second->fork_mutex);
}

void	dream(t_philo *philo)
{
	write_msg(philo->philo_id, "is sleeping\t   "EM_SLEEP, philo->data, 0);
	precise_usleep(philo->data->time_to_sleep, philo->data);
}
