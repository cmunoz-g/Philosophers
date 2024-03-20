#include "philo.h"

int	get_time(t_data *data)
{
	struct timeval time;

	if (gettimeofday(&time, NULL) == -1)
	{
		pthread_mutex_lock(&(data->error_mutex));
		data->error_flag = true;
		pthread_mutex_unlock(&(data->error_mutex));
		error("gettimeofday() failed"); 
	}
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	precise_usleep(int ms, t_data *data)
{
	int	start;

	start = get_time(data);
	while (get_time(data) - start < ms)
		if (usleep(500))
		{
			pthread_mutex_lock(&(data->error_mutex));
			data->error_flag = true;
			pthread_mutex_unlock(&(data->error_mutex));
			error("usleep() failed");
		}
}