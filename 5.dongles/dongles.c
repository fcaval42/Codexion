/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaval <fcaval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 10:54:00 by fcaval            #+#    #+#             */
/*   Updated: 2026/05/06 13:28:47 by fcaval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static long	get_request_priority(t_coder *coder)
{
	long	priority;

	if (coder->sim->args.scheduler == SCHED_FIFO_VAL)
		return (0);
	pthread_mutex_lock(&coder->state_mutex);
	priority = coder->deadline_ms;
	pthread_mutex_unlock(&coder->state_mutex);
	return (priority);
}

static int	can_take_dongle(t_dongle *dongle, int coder_id, long now,
	t_heap_entry *top)
{
	if (!heap_peek(&dongle->waiting_heap, top))
		return (0);
	if (top->coder_id != coder_id)
		return (0);
	if (!dongle->available)
		return (0);
	if (now < dongle->available_at_ms)
		return (0);
	return (1);
}

static int	grant_dongle(t_coder *coder, t_dongle *dongle, t_heap_entry *top)
{
	heap_pop(&dongle->waiting_heap, top);
	dongle->available = 0;
	pthread_mutex_unlock(&dongle->mutex);
	log_taken_dongle(coder->sim, coder->id);
	return (1);
}

int	take_dongle(t_coder *coder, t_dongle *dongle)
{
	t_heap_entry	top;
	long			now;
	long			priority;

	pthread_mutex_lock(&dongle->mutex);
	priority = get_request_priority(coder);
	if (!heap_push(&dongle->waiting_heap, priority, coder->id))
	{
		pthread_mutex_unlock(&dongle->mutex);
		return (0);
	}
	while (!sim_is_stopped(coder->sim))
	{
		now = get_time_ms();
		if (can_take_dongle(dongle, coder->id, now, &top))
		{
			return (grant_dongle(coder, dongle, &top));
		}
		pthread_mutex_unlock(&dongle->mutex);
		usleep(500);
		pthread_mutex_lock(&dongle->mutex);
	}
	pthread_mutex_unlock(&dongle->mutex);
	return (0);
}

void	release_dongle(t_sim *sim, t_dongle *dongle)
{
	pthread_mutex_lock(&dongle->mutex);
	dongle->available = 1;
	dongle->available_at_ms = get_time_ms() + sim->args.dongle_cooldown;
	pthread_mutex_unlock(&dongle->mutex);
}

//you can take it in after priority
	//printf("\nBONUS DEBUG request: coder=%d dongle=%d priority=%ld
	//deadline=%ld\n", coder->id, dongle->id, priority, coder->deadline_ms);

//you can take it in if(can_take_dongle)
	//printf("BONUS DEBUG grant: dongle=%d -> coder=%d top_priority=%ld\n",
	//dongle->id, coder->id, top.priority);