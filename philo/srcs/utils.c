/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmunoz-g <cmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 12:06:47 by cmunoz-g          #+#    #+#             */
/*   Updated: 2024/04/23 09:13:28 by cmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error(char *error_msg)
{
	printf("Error: %s\n", error_msg);
	exit(EXIT_FAILURE);
}

char	*get_color(char *message)
{
	if (message[0] == 'd')
		return (RED);
	else if (message[0] == 'h')
		return (WHITE);
	else if (message[3] == 's')
		return (TEAL);
	else if (message[3] == 'e')
		return (YELLOW);
	else if (message[3] == 't')
		return (GREEN);
	else
		return (NULL);
}

/**
 * write_msg
 *
 * Logs messages related to philosopher activities, such as eating, thinking,
 * sleeping, and dying. It ensures thread-safe output by locking the necessary
 * mutexes before printing. The function adjusts the timestamp from the start 
 * of the simulation and formats the message to include a philosopher ID,
 * action, color, and optionally a fork ID if related to fork operations.
 *
 * @param philo_id	The identifier of the philosopher the message is about.
 * @param message	The specific action or event to log (e.g., "is eating").
 * @param data 		Pointer to the shared data struct with sync. primitives.
 * @param fork_id	Optional parameter; if non-zero, it includes the fork ID 
 *					involved in the action.
 */

void	write_msg(int philo_id, char *message, t_data *data, int fork_id)
{
	int		ms;
	char	*color;

	color = get_color(message);
	pthread_mutex_lock(&(data->write_mutex));
	ms = get_time(data);
	pthread_mutex_lock(&(data->dead_mutex));
	if (!data->dead)
	{
		if (!fork_id)
			printf("%s%dms\t%d %s\n", color, (ms - data->start),
				philo_id, message);
		else
		{
			printf("%s%dms\t%d %s %d "EM_FORK, color, (ms - data->start),
				philo_id, message, fork_id);
			printf("\n");
		}
	}
	pthread_mutex_unlock(&(data->dead_mutex));
	pthread_mutex_unlock(&(data->write_mutex));
}

int	ft_isspace(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *nptr)
{
	int	neg;
	int	res;

	neg = 1;
	res = 0;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == 43 || *nptr == 45)
	{
		if (*nptr == '-')
			neg = -1;
		nptr++;
	}
	while (*nptr >= 48 && *nptr <= 57)
	{
		res = (res * 10) + (*nptr - '0');
		nptr++;
	}
	return (res * neg);
}
