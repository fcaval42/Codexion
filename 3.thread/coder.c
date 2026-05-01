/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaval <fcaval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 17:44:03 by fcaval            #+#    #+#             */
/*   Updated: 2026/05/01 15:47:34 by fcaval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	all_done(t_sim *sim)
{
	int	i;
	int	count;

	i = 0;
	while (i < sim->args.nb_coders)
	{
		pthread_mutex_lock(&sim->coders[i].state_mutex);
		count = sim->coders[i].compile_count;
		pthread_mutex_unlock(&sim->coders[i].state_mutex);
		if (count < sim->args.nb_compiles_required)
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
	pthread_mutex_lock(&coder->state_mutex);
	coder->last_compile_start_ms = get_time_ms();
	coder->deadline_ms = coder->last_compile_start_ms + \
		sim->args.time_to_burnout;
	pthread_mutex_unlock(&coder->state_mutex);
	log_compiling(sim, coder->id);
	if (!sleep_ms(sim, sim->args.time_to_compile))
		return (0);
	pthread_mutex_lock(&coder->state_mutex);
	coder->compile_count++;
	pthread_mutex_unlock(&coder->state_mutex);
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

	coder = (t_coder *)arg;
	if (coder->id % 2 == 0)
		usleep(1000);
	while (!sim_is_stopped(coder->sim))
	{
		first = coder->left;
		second = coder->right;
		if (first == second)
		{
			while (!sim_is_stopped(coder->sim))
				usleep(500);
			break ;
		}
		if (!take_dongle(coder, first))
			break ;
		if (!take_dongle(coder, second))
		{
			release_dongle(coder->sim, first);
			break;
		}
		if (!do_compile(coder))
		{
			release_dongle(coder->sim, second);
			release_dongle(coder->sim, first);
			break ;
		}
		release_dongle(coder->sim, second);
		release_dongle(coder->sim, first);
		if (!do_debug(coder))
			break ;
		if (!do_refactor(coder))
			break ;
	}
	return (NULL);
}

