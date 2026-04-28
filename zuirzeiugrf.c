#include "../include/codexion.h"

/* ── Helpers ─────────────────────────────────────────────────────── */

/*
** Check if every coder has compiled enough times.
** Called after each compile to decide if we should stop.
*/
static int	all_done(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->args.nb_coders)
	{
		if (sim->coders[i].compile_count < sim->args.nb_compiles_required)
			return (0);
		i++;
	}
	return (1);
}

/* ── Coder phases ────────────────────────────────────────────────── */

/*
** TODO (next step): acquire left and right dongles before compiling.
** For now we skip straight to compiling so we can test the thread loop.
*/
static int	do_compile(t_coder *coder)
{
	t_sim	*sim;

	sim = coder->sim;
	/* record when we started compiling — used for EDF deadline */
	coder->last_compile_start_ms = get_time_ms();
	coder->deadline_ms = coder->last_compile_start_ms
		+ sim->args.time_to_burnout;
	log_compiling(sim, coder->id);
	if (!sleep_ms(sim, sim->args.time_to_compile))
		return (0);
	/* TODO: release dongles here */
	coder->compile_count++;
	if (all_done(sim))
	{
		sim_stop(sim);
		return (0);
	}
	return (1);
}

static int	do_debug(t_coder *coder)
{
	t_sim	*sim;

	sim = coder->sim;
	log_debugging(sim, coder->id);
	return (sleep_ms(sim, sim->args.time_to_debug));
}

static int	do_refactor(t_coder *coder)
{
	t_sim	*sim;

	sim = coder->sim;
	log_refactoring(sim, coder->id);
	return (sleep_ms(sim, sim->args.time_to_refactor));
}

/* ── Thread entry point ──────────────────────────────────────────── */

/*
** Each coder runs this loop:
**   [acquire dongles] → compile → [release dongles] → debug → refactor → repeat
**
** The loop exits when sim_is_stopped() returns true (burnout or all done).
*/
void	*coder_routine(void *arg)
{
	t_coder	*coder;

	coder = (t_coder *)arg;
	/* Small stagger so not every coder tries to grab dongles at t=0.
	** Odd-indexed coders wait 1ms — classic trick to avoid deadlock
	** even before we implement proper scheduling. */
	if (coder->id % 2 == 0)
		usleep(1000);
	while (!sim_is_stopped(coder->sim))
	{
		/* TODO: acquire_dongles(coder) */
		if (!do_compile(coder))
			break ;
		if (!do_debug(coder))
			break ;
		if (!do_refactor(coder))
			break ;
	}
	return (NULL);
}