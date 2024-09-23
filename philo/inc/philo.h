/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmunoz-g <cmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:07:22 by cmunoz-g          #+#    #+#             */
/*   Updated: 2024/04/20 11:38:32 by cmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/time.h>
# include <stdlib.h>
# define YELLOW "\x1b[33m" // eating
# define TEAL "\033[0;36m" // sleeping
# define GREEN "\x1b[32m" // thinking
# define RED "\x1b[31m" // died
# define WHITE "\033[0;37m"
# define EM_DEAD "💀"
# define EM_EAT "🍕"
# define EM_SLEEP "😴"
# define EM_FORK "🍴"
# define EM_THINK "🤯"

typedef struct s_data	t_data;

typedef struct s_fork
{
	pthread_mutex_t	fork_mutex;
	int				fork_id;
}				t_fork;

typedef struct s_philo
{
	pthread_t		thread_id;
	int				philo_id;
	int				num_meals;
	int				last_meal;
	bool			full;
	t_fork			*left_fork;
	t_fork			*right_fork;
	struct s_data	*data;
}				t_philo;

typedef struct s_data
{
	int				nbr_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nbr_max_meals;
	int				start;
	int				argc;
	bool			dead;
	bool			error_flag;
	pthread_mutex_t	error_mutex;
	pthread_mutex_t	dead_mutex;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	write_mutex;
	t_philo			*philos;
	t_fork			*forks;
}				t_data;

// actions.c
void	dream(t_philo *philo);
void	eat(t_philo *philo);
void	eat_aux(t_philo *philo, t_fork *first, t_fork *second);
void	think(t_philo *philo);

// checks.c
void	check_input(int argc, char **argv, t_data *data);
void	check_nbr(char *str);
int		check_end(t_philo *philo);
int		check_full(t_data *data);
int		check_error(t_philo *philo);

// clean.c
void	clean(t_data *data);
void	clean_mutex(t_data *data, int mutex_flag);
void	clean_fork_mutex(t_data *data, int fork_mutex_flag);

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
int		get_time(t_data *data);
void	precise_usleep(int ms, t_data *data);

// utils.c
int		ft_atoi(const char *nptr);
int		ft_isspace(char c);
void	write_msg(int philo_id, char *message, t_data *data, int fork_id);
void	error(char *error_msg);
char	*get_color(char *message);

// main.c 
int		main(int argc, char *argv[]);
#endif