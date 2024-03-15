#include "philo.h"

int	get_time(int start_time)
{
	struct timeval time;

	if (gettimeofday(&time, NULL) == -1)
		error("gettimeofday() failed"); // que pasa si esto sucede dentro de uno de los philo threads???? , terminaria pero el resto seguirian?, deberia parar toda la simulacion?
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000) - start_time);
}

void	precise_usleep(t_data *data, int ms)
{
	int	start;

	start = get_time(data->start);
	while ((get_time(data->start) - start) < ms)
		if (usleep(50)) // 500 o 50?
			error("usleep() failed"); // lo mismo que en el error de get time
}