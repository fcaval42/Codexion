/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaval <fcaval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 13:39:02 by fcaval            #+#    #+#             */
/*   Updated: 2026/05/04 15:40:19 by fcaval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	coder_is_burned(t_sim *sim, int i, long now)
{
	int		count;
	long	deadline;

	pthread_mutex_lock(&sim->coders[i].state_mutex);
	count = sim->coders[i].compile_count;
	deadline = sim->coders[i].deadline_ms;
	pthread_mutex_unlock(&sim->coders[i].state_mutex);
	if (count >= sim->args.nb_compiles_required)
		return (0);
	if (deadline == 0)
		return (0);
	if (now >= deadline)
		return (1);
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_sim	*sim;
	long	now;
	int		i;

	sim = (t_sim *)arg;
	while (!sim_is_stopped(sim))
	{
		now = get_time_ms();
		i = 0;
		while (i < sim->args.nb_coders)
		{
			if (coder_is_burned(sim, i, now))
			{
				log_burnout(sim, sim->coders[i].id);
				sim_stopped(sim);
				return (NULL);
			}
			i++;
		}
		usleep(500);
	}
	return (NULL);
}
