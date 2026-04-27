/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaval <fcaval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 10:48:04 by fcaval            #+#    #+#             */
/*   Updated: 2026/04/27 16:58:55 by fcaval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CONEXION_H

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>


typedef struct s_args
{
	int		nb_coders;
	long	time_to_burnout;
	long	time_to_compile;
	long	time_to_debug;
	long	time_to_refractor;
	int		nb_compiles_required;
	long	dongle_cooldown;
	int		scheduler;
}	t_args;

// ------ PARSING ------ //

int		parse_scheduler(const char *str, int *scheduler);
int		parse_numeric_args(char **argv, t_args *args);
int		parse_args(int argc, char **argv, t_args *args);

// ------ UTILS ------ //

int		ft_is_digit(int c);
long	ft_atol(const char *str);
int		ft_is_valid_integer(const char *str);
void	ft_putstr_err(const char *message);


#endif