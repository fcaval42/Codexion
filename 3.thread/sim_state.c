/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_state.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaval <fcaval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 11:56:08 by fcaval            #+#    #+#             */
/*   Updated: 2026/04/29 16:57:39 by fcaval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	sim_is_stopped(t_sim *sim)
{
	int	stopped;

	pthread_mutex_lock(&sim->stop_mutex);
	stopped = sim->stop;
	pthread_mutex_unlock(&sim->stop_mutex);
	return (stopped);
}

void	sim_stopped(t_sim *sim)
{
	pthread_mutex_lock(&sim->stop_mutex);
	sim->stop = 1;
	pthread_mutex_unlock(&sim->stop_mutex);
}

int	sleep_ms(t_sim *sim, long ms)
{
	long	start;
	long	elapsed;

	start = get_time_ms();
	while (1)
	{
		if (sim_is_stopped(sim))
			return (0);
		elapsed = get_time_ms() - start;
		if (elapsed >= ms)
			return (1);
		usleep(500);
	}
}
