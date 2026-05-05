/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaval <fcaval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 10:48:04 by fcaval            #+#    #+#             */
/*   Updated: 2026/05/05 10:56:28 by fcaval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <stddef.h>

# define SCHED_FIFO_VAL 0
# define SCHED_EDF_VAL  1

typedef struct s_heap_entry
{
	long			priority;
	unsigned long	seq;
	int				coder_id;
}	t_heap_entry;

typedef struct s_heap
{
	t_heap_entry	*data;
	int				size;
	int				capacity;
	unsigned long	next_seq;
}	t_heap;

typedef struct s_args
{
	int		nb_coders;
	long	time_to_burnout;
	long	time_to_compile;
	long	time_to_debug;
	long	time_to_refactor;
	int		nb_compiles_required;
	long	dongle_cooldown;
	int		scheduler;
}	t_args;

typedef struct s_dongle
{
	int				id;
	int				available;
	long			available_at_ms;
	t_heap			waiting_heap;
	pthread_mutex_t	mutex;
	pthread_cond_t	cond;
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
	pthread_mutex_t	state_mutex;
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

int		parse_args(int argc, char **argv, t_args *args);

// ------ UTILS ------ //

int		ft_is_digit(int c);
long	ft_atol(const char *str);
int		ft_is_valid_integer(const char *str);
void	ft_putstr_err(const char *message);
long	get_time_ms(void);

// ------ INIT ------ //

int		init_sim(t_sim *sim, t_args *args);
void	clean_sim(t_sim *sim);

// ------ SIM_STATE ------ //

long	get_time_ms(void);
int		sleep_ms(t_sim *sim, long ms);
int		sim_is_stopped(t_sim *sim);
void	sim_stopped(t_sim *sim);

// ------ LOGS ------ //

void	log_state(t_sim *sim, int coder_id, const char *state);
void	log_taken_dongle(t_sim *sim, int coder_id);
void	log_compiling(t_sim *sim, int coder_id);
void	log_debugging(t_sim *sim, int coder_id);
void	log_refactoring(t_sim *sim, int coder_id);
void	log_burnout(t_sim *sim, int coder_id);

// ------ CODER ------ //

void	*coder_routine(void *arg);
int		do_compile(t_coder *coder);
int		do_refactor(t_coder *coder);
int		do_debug(t_coder *coder);

// ------ HEAP ------ //

int		heap_init(t_heap *heap, int capacity);
int		heap_push(t_heap *heap, long pritority, int coder_id);
int		heap_pop(t_heap *heap, t_heap_entry *out);

// ------ HEAP UTILS ------ //

int		heap_peek(t_heap *heap, t_heap_entry *out);
int		heap_empty(t_heap *heap);
void	heap_destroy(t_heap *heap);

// ------ HEAP SORT ------ //

void	sift_up(t_heap *heap, int index);
void	sift_down(t_heap *heap, int index);

// ------ HEAP SORT UTILS ------ //

int		has_higher_priority(t_heap_entry a, t_heap_entry b);
int		parent_index(int index);
int		left_index(int index);
int		right_index(int index);
void	swap_entries(t_heap *heap, int a, int b);

// ------ DONGLES ------ //

int		take_dongle(t_coder *coder, t_dongle *dongle);
void	release_dongle(t_sim *sim, t_dongle *dongle);

// ------ MONITOR ------ //

void	*monitor_routine(void *arg);

#endif
