/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaval <fcaval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 11:27:06 by fcaval            #+#    #+#             */
/*   Updated: 2026/05/01 14:26:45 by fcaval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	lauch_threads(t_sim *sim)
{
	int	i;

	sim->start_ms = get_time_ms();
	i = 0;
	while (i < sim->args.nb_coders)
	{
		if (pthread_create(&sim->coders[i].thread, NULL, coder_routine, \
			&sim->coders[i]) != 0)
			return (0);
		i++;
	}
	if (pthread_create(&sim->monitor, NULL, monitor_routine, sim) != 0)
		return (0);
	return (1);
}

void	join_threads(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->args.nb_coders)
	{
		pthread_join(sim->coders[i].thread, NULL);
		i++;
	}
	pthread_join(sim->monitor, NULL);
}

int	main(int argc, char **argv)
{
	t_args	args;
	t_sim	sim;

	memset(&args, 0, sizeof(t_args));
	if (!parse_args(argc, argv, &args))
		return (1);
	if (!init_sim(&sim, &args))
	{
		ft_putstr_err("⚠️ Error: simulation initialisation failed.\n");
		clean_sim(&sim);
		return (1);
	}
	if (!lauch_threads(&sim))
	{
		ft_putstr_err("⚠️ Error: thread creation failed.\n");
		clean_sim(&sim);
		return (1);
	}
	join_threads(&sim);
	clean_sim(&sim);
	return (0);
}
