#include "philo.h"

// arreglar para que salga el mensaje de morir el ultimo

// arreglar para limpiar todos los threads si falla 1

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
