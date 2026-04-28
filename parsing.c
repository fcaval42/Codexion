/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaval <fcaval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 10:53:21 by fcaval            #+#    #+#             */
/*   Updated: 2026/04/28 17:18:02 by fcaval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	parse_scheduler(const char *str, t_args *args)
{
	if (strcmp(str, "fifo") == 0 || strcmp(str, "edf") == 0)
	{
		if (strcmp(str, "fifo") == 0)
			args->scheduler = SCHED_FIFO_VAL;
		else
			args->scheduler = SCHED_EDF_VAL;
		return (1);
	}
	return (0);
}

int	parse_numeric_args(char **argv, t_args *args)
{
	int	i;

	i = 1;
	while (i <= 7)
	{
		if (!ft_is_valid_integer(argv[i]))
			return (0);
		i++;
	}
	args->nb_coders = atoi(argv[1]);
	args->time_to_burnout = ft_atol(argv[2]);
	args->time_to_compile = ft_atol(argv[3]);
	args->time_to_debug = ft_atol(argv[4]);
	args->time_to_refractor = ft_atol(argv[5]);
	args->nb_compiles_required = atoi(argv[6]);
	args->dongle_cooldown = ft_atol(argv[7]);
	if (args->nb_coders < 1)
		return (0);
	if (args->nb_compiles_required < 1)
		return (0);
	return (1);
}

int	parse_args(int argc, char **argv, t_args *args)
{
	if (argc != 9)
	{
		ft_putstr_err("⚠️​ Error: It must have 8 arguments\n");
		ft_putstr_err("    Usage: \n");
		ft_putstr_err("codexion <number_of_coders> <time_to_burnout> \
			<time_to_compile> <time_to_debug> <time_to_refactor> \
			<number_of_compiles_required> <dongle_cooldown> <scheduler>\n");
		return (0);
	}
	if (!parse_numeric_args(argv, args))
	{
		ft_putstr_err("⚠️ Error: Invalid numeric argument \
			(must be a positive integer)\n");
		return (0);
	}
	if (!parse_scheduler(argv[8], args))
	{
		ft_putstr_err("⚠️ Error: scheduler must be 'fifo' or 'edf'.\n");
		return (0);
	}
	return (1);
}
