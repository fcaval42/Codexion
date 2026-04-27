/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaval <fcaval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 11:27:06 by fcaval            #+#    #+#             */
/*   Updated: 2026/04/27 17:00:16 by fcaval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	main(int argc, char **argv)
{
	t_args	args;

	memset(&args, 0, sizeof(t_args));
	if (!parse_args(argc, argv, &args))
		return (1);

	printf("coders : %d\n", args.nb_coders);
	printf("time to burnout: %ld\n", args.time_to_burnout);
	printf("time to compile: %ld\n", args.time_to_compile);
	printf("time to debug: %ld\n", args.time_to_debug);
	printf("time to refactor: %ld\n", args.time_to_refractor);
	printf("number of compiles: %d\n", args.nb_compiles_required);
	printf("dongle cooldown: %ld\n", args.dongle_cooldown);
	printf("scheduler: %d\n", args.scheduler);
}


// ==== voir pourquoi ça fonctionne pas lol
