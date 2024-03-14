#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

typedef struct	s_data;

typedef	struct	s_fork
{
	pthread_mutex_t fork_mutex;
	int				fork_id;
}				t_fork;

typedef struct	s_philo
{
	pthread_t		thread_id;
	int				philo_id;
	int				num_meals;
	int				last_meal;
	t_fork			*left_fork;
	t_fork			*right_fork;
	struct s_data	*data;
}				t_philo;

typedef struct	s_data
{
	int				nbr_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nbr_max_meals;
	int				start;
	bool			max_meals_arg;
	bool			dead;
	bool			full;
	pthread_mutex_t	dead_mutex;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	write_mutex;
	t_philo			*philos;
	t_fork			*forks;
}				t_data;

void	write_message(int philo_id, char *message, t_data *data);

#endif