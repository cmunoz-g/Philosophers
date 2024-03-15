#include "philo.h"

// gestionar el segv con ./philo 4 310 200 100

int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc == 5 || argc == 6)
	{
		check_input(argc, argv, &data);
		init_data(&data);
		create_threads(&data);
		clean(&data); // quiza no haga falta tener esto aqui, sino que lo llame la ft que checkea si han comido x veces o uno ha muerto
	}
	else
		error("Wrong number of arguments");
	return (0);
}