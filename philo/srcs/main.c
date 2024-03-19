#include "philo.h"

// ver que hacer con los error return de los mutex init

// revisar lo del >= en time_to_die (monitoring.c)

// colores 

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
