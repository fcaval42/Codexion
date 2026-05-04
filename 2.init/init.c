/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaval <fcaval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 13:29:13 by fcaval            #+#    #+#             */
/*   Updated: 2026/05/04 18:35:16 by fcaval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	init_dongles(t_sim *sim)
{
	int	n;
	int	i;

	n = sim->args.nb_coders;
	sim->dongles = malloc(sizeof(t_dongle) * n);
	if (!sim->dongles)
		return (0);
	i = 0;
	while (i < n)
	{
		sim->dongles[i].id = i;
		sim->dongles[i].available = 1;
		sim->dongles[i].available_at_ms = 0;
		if (!heap_init(&sim->dongles[i].waiting_heap, sim->args.nb_coders))
			return (0);
		if (pthread_mutex_init(&sim->dongles[i].mutex, NULL) != 0)
			return (0);
		if (pthread_cond_init(&sim->dongles[i].cond, NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

static int	init_coders(t_sim *sim)
{
	int	n;
	int	i;

	i = 0;
	n = sim->args.nb_coders;
	sim->coders = malloc(sizeof(t_coder) * n);
	if (!sim->coders)
		return (0);
	while (i < n)
	{
		if (pthread_mutex_init(&sim->coders[i].state_mutex, NULL) != 0)
			return (0);
		sim->coders[i].id = i + 1;
		sim->coders[i].compile_count = 0;
		sim->coders[i].last_compile_start_ms = 0;
		sim->coders[i].deadline_ms = 0;
		sim->coders[i].left = (&sim->dongles[i]);
		sim->coders[i].right = (&sim->dongles[(i + 1) % n]);
		sim->coders[i].sim = sim;
		i++;
	}
	return (1);
}

int	init_sim(t_sim *sim, t_args *args)
{
	memset(sim, 0, sizeof(t_sim));
	sim->args = *args;
	sim->stop = 0;
	if (pthread_mutex_init(&sim->log_mutex, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&sim->stop_mutex, NULL) != 0)
		return (0);
	if (!init_dongles(sim))
		return (0);
	if (!init_coders(sim))
		return (0);
	return (1);
}
