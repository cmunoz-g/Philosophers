#include "philo.h"

int		check_end(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->dead_mutex));
	if (philo->data->dead)
	{
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
	if (data->nbr_philos <= 0) // comprobar si deberia meter limite para 200
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
		data->nbr_max_meals = ft_atoi(argv[5]); // revisar el caso en el que nbr_max_meals es 0
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