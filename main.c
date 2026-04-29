/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaval <fcaval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 11:27:06 by fcaval            #+#    #+#             */
/*   Updated: 2026/04/29 14:51:52 by fcaval           ###   ########.fr       */
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

//printf("coders : %d\n", args.nb_coders);
//printf("time to burnout: %ld\n", args.time_to_burnout);
//printf("time to compile: %ld\n", args.time_to_compile);
//printf("time to debug: %ld\n", args.time_to_debug);
//printf("time to refactor: %ld\n", args.time_to_refractor);
//printf("number of compiles: %d\n", args.nb_compiles_required);
//printf("dongle cooldown: %ld\n", args.dongle_cooldown);
//printf("scheduler: %d\n", args.scheduler);
//return (0);
