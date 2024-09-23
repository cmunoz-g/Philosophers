/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmunoz-g <cmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 11:43:27 by cmunoz-g          #+#    #+#             */
/*   Updated: 2024/06/11 10:51:44 by cmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
