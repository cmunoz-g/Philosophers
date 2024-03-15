#include "philo.h"

void	think(t_philo *philo)
{
	write_message(philo->philo_id, "is thinking", philo->data);
} 

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&(philo->right_fork->fork_mutex));
	write_message(philo->philo_id, "has taken a fork", philo->data);
	pthread_mutex_lock(&(philo->left_fork->fork_mutex));
	write_message(philo->philo_id, "has taken a fork", philo->data);
	write_message(philo->philo_id, "is eating", philo->data);
	pthread_mutex_lock(&(philo->data->meal_mutex));
	philo->last_meal = get_time(philo->data->start); 
	philo->num_meals++;
	pthread_mutex_unlock(&(philo->data->meal_mutex));
	precise_usleep(philo->data, philo->data->time_to_eat);
	pthread_mutex_unlock(&(philo->right_fork->fork_mutex));
	pthread_mutex_unlock(&(philo->left_fork->fork_mutex));
}

void	dream(t_philo *philo)
{
	write_message(philo->philo_id, "is sleeping", philo->data);
	precise_usleep(philo->data, philo->data->time_to_sleep);
}