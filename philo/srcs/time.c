#include "philo.h"

int	get_time(void)
{
	struct timeval time;
	//start_time += 0;

	if (gettimeofday(&time, NULL) == -1)
		error("gettimeofday() failed"); // que pasa si esto sucede dentro de uno de los philo threads???? , terminaria pero el resto seguirian?, deberia parar toda la simulacion?
	//return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	precise_usleep(int ms)
{
	int	start;

	start = get_time();
	while (get_time() - start < ms)
		if (usleep(500)) // 500 o 50?
			error("usleep() failed"); // lo mismo que en el error de get time
}