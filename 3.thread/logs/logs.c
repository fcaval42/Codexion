/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaval <fcaval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 13:39:35 by fcaval            #+#    #+#             */
/*   Updated: 2026/04/29 13:42:52 by fcaval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	log_taken_dongle(t_sim *sim, int coder_id)
{
	log_state(sim, coder_id, "has taken a dongle");
}

void	log_compiling(t_sim *sim, int coder_id)
{
	log_state(sim, coder_id, "is compiling");
}

void	log_debugging(t_sim *sim, int coder_id)
{
	log_state(sim, coder_id, "is debugging");
}

void	log_refactoring(t_sim *sim, int coder_id)
{
	log_state(sim, coder_id, "is refactoring");
}

void	log_burnout(t_sim *sim, int coder_id)
{
	log_state(sim, coder_id, "burned out");
}
