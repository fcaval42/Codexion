/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaval <fcaval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 10:48:04 by fcaval            #+#    #+#             */
/*   Updated: 2026/04/28 17:39:51 by fcaval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <pthread.h>

# define SCHED_FIFO_VAL 0
# define SCHED_EDF_VAL  1

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

typedef struct s_dongle
{
	int					id;
	int					available;
	long				available_at_ms;
	pthread_mutex_t		mutex;
	pthread_cond_t		cond;
}	t_dongle;

typedef struct s_coder
{
	int				id;
	int				compile_count;
	long			last_compile_start_ms;
	long			deadline_ms;
	t_dongle		*left;
	t_dongle		*right;
	pthread_t		thread;
	struct s_sim	*sim;
}	t_coder;

typedef struct s_sim
{
	t_args			args;
	t_coder			*coders;
	t_dongle		*dongles;
	long			start_ms;
	int				stop;
	pthread_mutex_t	log_mutex;
	pthread_mutex_t	stop_mutex;
	pthread_t		monitor;
}	t_sim;

// ------ PARSING ------ //

int		parse_scheduler(const char *str, t_args *args);
int		parse_numeric_args(char **argv, t_args *args);
int		parse_args(int argc, char **argv, t_args *args);

// ------ UTILS ------ //

int		ft_is_digit(int c);
long	ft_atol(const char *str);
int		ft_is_valid_integer(const char *str);
void	ft_putstr_err(const char *message);

// ------ INIT ------ //

int		init_dongles(t_sim *sim);
int		init_coders(t_sim *sim);
int		init_sim(t_sim *sim, t_args *args);
void	clean_sim(t_sim *sim);

#endif
