#include "philo.h"

void	error(char *error_msg)
{
	printf("Error: %s\n", error_msg);
	exit(EXIT_FAILURE);
}

void	write_message(int philo_id, char *message, t_data *data) // meter colores y demas, meter que si cogen un tenedor diga que tenedor es?
{
	int	ms;

	pthread_mutex_lock(&(data->write_mutex));
	ms = get_time(data->start);
	pthread_mutex_lock(&(data->dead_mutex));
	if (!data->dead)
		printf("%dms	%d %s\n", ms, philo_id, message); 
	pthread_mutex_unlock(&(data->dead_mutex));
	pthread_mutex_unlock(&(data->write_mutex));
}

int	ft_isspace(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *nptr)
{
	int	neg;
	int	res;

	neg = 1;
	res = 0;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == 43 || *nptr == 45)
	{
		if (*nptr == '-')
			neg = -1;
		nptr++;
	}
	while (*nptr >= 48 && *nptr <= 57)
	{
		res = (res * 10) + (*nptr - '0');
		nptr++;
	}
	return (res * neg);
}