#include "philo.h"

// PROBLEMA LOS MUTEX DE LOS FORKS NO LOS RECONOCE
// PARECE QUE EL MUTEX DE WRITE TAMPOCO???

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
