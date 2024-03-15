#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/time.h>
# include <stdlib.h>

typedef struct	s_data	t_data;

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
	int				finished;
	bool			max_meals_arg;
	bool			dead;
	pthread_mutex_t	dead_mutex;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	write_mutex;
	t_philo			*philos;
	t_fork			*forks;
}				t_data;

// actions.c
void	dream(t_philo *philo);
void	eat(t_philo *philo);
void	think(t_philo *philo);

// checks.c
void	check_input(int argc, char **argv, t_data *data);
void	check_nbr(char *str);
int		check_end(t_philo *philo);

// clean.c
void	clean(t_data *data);

// dinner.c
void	*dinner(void *philo);
void	create_threads(t_data *data);

// init.c
void	init_data(t_data *data);
void	init_philos(t_data *data);
void	init_forks(t_data *data);

// monitoring.c
void	*monitoring(void *data);
int		full_status(t_data *data);
int		dead_status(t_data *data);

// time.c
int		get_time(int start_time);
void	precise_usleep(t_data *data, int ms);

// utils.c
int		ft_atoi(const char *nptr);
int		ft_isspace(char c);
void	write_message(int philo_id, char *message, t_data *data);
void	error(char *error_msg);

// main.c 
int	main(int argc, char *argv[]);
#endif