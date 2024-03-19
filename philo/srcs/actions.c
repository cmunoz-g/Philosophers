#include "philo.h"

void	think(t_philo *philo)
{
	write_message(philo->philo_id, "is thinking\t   "EM_THINK, philo->data, 0, GREEN);
} 

void	eat(t_philo *philo)
{
	t_fork *first;
	t_fork *second;

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

void	eat_aux(t_philo *philo, t_fork *first, t_fork *second)
{
	pthread_mutex_lock(&first->fork_mutex);
	write_message(philo->philo_id, "has taken fork", philo->data, first->fork_id, WHITE);
	if (philo->data->nbr_philos == 1)
	{
		precise_usleep(philo->data->time_to_die, philo->data);
		pthread_mutex_unlock(&first->fork_mutex);
		return ;
	}
	pthread_mutex_lock(&second->fork_mutex);
	write_message(philo->philo_id, "has taken fork", philo->data, second->fork_id, WHITE);
	write_message(philo->philo_id, "is eating\t   "EM_EAT, philo->data, 0, YELLOW);
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
	write_message(philo->philo_id, "is sleeping\t   "EM_SLEEP, philo->data, 0, TEAL);
	precise_usleep(philo->data->time_to_sleep, philo->data);
}

/*
void	eat_aux(t_philo *philo, t_fork *first, t_fork *second)
{
	pthread_mutex_lock(&(philo->right_fork->fork_mutex));
	write_message(philo->philo_id, "has taken fork number", philo->data, philo->right_fork->fork_id);
	if (philo->data->nbr_philos == 1)
	{
		precise_usleep(philo->data->time_to_die);
		pthread_mutex_unlock(&(philo->right_fork->fork_mutex));
		return ;
	}
	pthread_mutex_lock(&(philo->left_fork->fork_mutex));
	write_message(philo->philo_id, "has taken fork number", philo->data, philo->left_fork->fork_id);
	write_message(philo->philo_id, "is eating", philo->data, 0);
	pthread_mutex_lock(&(philo->data->meal_mutex));
	philo->last_meal = get_time(); 
	//printf("last meal time: %d\n",philo->last_meal);
	philo->num_meals++;
	pthread_mutex_unlock(&(philo->data->meal_mutex));
	precise_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(&(philo->right_fork->fork_mutex));
	pthread_mutex_unlock(&(philo->left_fork->fork_mutex));
}*/