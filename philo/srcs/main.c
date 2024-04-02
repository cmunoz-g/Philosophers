#include "philo.h"

// revisar el delay de 1 ms para que salga al final el msg de muerte
// cuando pongo nbr max meals deberia salir el ultimo mensaje el de comer?
// revisar nbr max meals a 0

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
