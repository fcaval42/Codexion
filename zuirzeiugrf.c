#include "../include/codexion.h"

int	main(int argc, char **argv)
{
	t_args	args;

	memset(&args, 0, sizeof(t_args));
	if (!parse_args(argc, argv, &args))
		return (1);
	/* ── Debug print (remove later) ── */
	printf("coders         : %d\n", args.nb_coders);
	printf("time_to_burnout: %ld ms\n", args.time_to_burnout);
	printf("time_to_compile: %ld ms\n", args.time_to_compile);
	printf("time_to_debug  : %ld ms\n", args.time_to_debug);
	printf("time_to_refactor:%ld ms\n", args.time_to_refactor);
	printf("compiles_req   : %d\n", args.nb_compiles_required);
	printf("dongle_cooldown: %ld ms\n", args.dongle_cooldown);
	printf("scheduler      : %s\n", args.scheduler == SCHED_FIFO_VAL
		? "fifo" : "edf");
	return (0);
}