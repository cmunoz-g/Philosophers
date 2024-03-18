#include "philo.h"

// arreglar el problema de 1 philo solo

// con 5 800 200 200  y  5 800 200 200 7 el 1 se muere :(

// con 4 410 200 200 el 1 se muere

// arreglar para que salga el mensaje de morir el ultimo


int	main(int argc, char *argv[])
{
	t_data	data;

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
