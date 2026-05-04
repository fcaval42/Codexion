/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_state.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaval <fcaval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 13:30:40 by fcaval            #+#    #+#             */
/*   Updated: 2026/05/04 18:05:25 by fcaval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	log_state(t_sim *sim, int coder_id, const char *state)
{
	long	ts;

	ts = get_time_ms() - sim->start_ms;
	pthread_mutex_lock(&sim->log_mutex);
	printf("[%ld] %d %s\n", ts, coder_id, state);
	pthread_mutex_unlock(&sim->log_mutex);
}
