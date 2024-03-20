#include "philo.h"

// revisar lo del >= en time_to_die (monitoring.c)

// pasar leaks en 42 Mac

// void	leaks(void)
// {
// 	system("leaks philo");
// }

int	main(int argc, char *argv[])
{
	t_data	data;

	// atexit(leaks);
	if (argc == 5 || argc == 6)
	{
		check_input(argc, argv, &data);
		init_data(&data);
		create_threads(&data);
		clean(&data); 
	}
	else
		error("Wrong number of arguments");
	return (0);
}
