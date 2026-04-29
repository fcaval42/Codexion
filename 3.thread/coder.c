/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaval <fcaval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 17:44:03 by fcaval            #+#    #+#             */
/*   Updated: 2026/04/29 16:58:16 by fcaval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	all_done(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->args.nb_coders)
	{
		if (sim->coders[i].compile_count < sim->args.nb_compiles_required)
			return (0);
		i++;
	}
	return (1);
}

static int	do_debug(t_coder *coder)
{
	t_sim	*sim;

	sim = coder->sim;
	log_debugging(sim, coder->id);
	return (sleep_ms(sim, sim->args.time_to_debug));
}

static int	do_refactor(t_coder *coder)
{
	t_sim	*sim;

	sim = coder->sim;
	log_refactoring(sim, coder->id);
	return (sleep_ms(sim, sim->args.time_to_refactor));
}

static int	do_compile(t_coder *coder)
{
	t_sim	*sim;

	sim = coder->sim;
	coder->last_compile_start_ms = get_time_ms();
	coder->deadline_ms = coder->last_compile_start_ms + \
	sim->args.time_to_burnout;
	log_compiling(sim, coder->id);
	if (!sleep_ms(sim, sim->args.time_to_compile))
		return (0);
	coder->compile_count++;
	if (all_done(sim))
	{
		sim_stopped(sim);
		return (0);
	}
	return (1);
}

void	*coder_routine(void *arg)
{
	t_coder		*coder;
	t_dongle	*first;
	t_dongle	*second;
	t_dongle	*tmp;

	coder = (t_coder *)arg;
	if (coder->id % 2 == 0)
		usleep(1000);
	while (!sim_is_stopped(coder->sim))
	{
		first = coder->left;
		second = coder->right;
		if (first->id > second->id)
		{
			tmp = first;
			first = second;
			second = tmp;
		}
		pthread_mutex_lock(&first->mutex);
		if (second != first)
			pthread_mutex_lock(&second->mutex);
		if (!do_compile(coder))
			break ;
		if (!do_debug(coder))
			break ;
		if (!do_refactor(coder))
			break ;
	}
	return (NULL);
}
