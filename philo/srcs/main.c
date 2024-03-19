#include "philo.h"

// con 4 410 200 200 hay muerte y deadlock

// arreglar que cuando le metemos limite de comidas, coman todos. ademas, que termine con otro mensaje

// arreglar para que salga el mensaje de morir el ultimo

// arreglar para limpiar todos los threads si falla 1

// colores 

void	whichforks(t_data data) // borrar
{
	int j = 0;

	while (j < data.nbr_philos)
	{
		printf("%d has left fork %d and right fork %d\n",j + 1, data.philos[j].left_fork->fork_id, data.philos[j].right_fork->fork_id);
		j++;
	}
	exit(0);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc == 5 || argc == 6)
	{
		check_input(argc, argv, &data);
		init_data(&data);
		//whichforks(data);
		create_threads(&data);
		clean(&data); 
	}
	else
		error("Wrong number of arguments");
	return (0);
}
