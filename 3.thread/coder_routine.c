/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaval <fcaval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 18:26:36 by fcaval            #+#    #+#             */
/*   Updated: 2026/05/04 18:27:05 by fcaval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	wait_for_stop(t_coder *coder)
{
	while (!sim_is_stopped(coder->sim))
		usleep(500);
	return (0);
}

static int	acquire_dongles(t_coder *coder, t_dongle *first, t_dongle *second)
{
	if (first == second)
		return (wait_for_stop(coder));
	if (!take_dongle(coder, first))
		return (0);
	if (!take_dongle(coder, second))
	{
		release_dongle(coder->sim, first);
		return (0);
	}
	return (1);
}

static int	run_cycle(t_coder *coder, t_dongle *first, t_dongle *second)
{
	if (!do_compile(coder))
	{
		release_dongle(coder->sim, second);
		release_dongle(coder->sim, first);
		return (0);
	}
	release_dongle(coder->sim, second);
	release_dongle(coder->sim, first);
	if (!do_debug(coder))
		return (0);
	return (do_refactor(coder));
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
		if (!acquire_dongles(coder, first, second))
			break ;
		if (!run_cycle(coder, first, second))
			break ;
	}
	return (NULL);
}
