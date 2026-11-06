#include "push_swap.h"

static void	free_all(t_ctx *ctx)
{
	stack_clear(&ctx->a);
	stack_clear(&ctx->b);
}

static void	run_strategy(t_ctx *ctx)
{
	if (ctx->strat == STRAT_SIMPLE)
		sort_simple(ctx);
	else if (ctx->strat == STRAT_MEDIUM)
		sort_medium(ctx);
	else if (ctx->strat == STRAT_COMPLEX)
		sort_complex(ctx);
	else
		sort_adaptive(ctx);
}

int	main(int ac, char **av)
{
	t_ctx	ctx;

	if (ac < 2)
		return (0);
	ctx = (t_ctx){0};
	ctx.strat = STRAT_ADAPTIVE;
	if (!parse_args(&ctx, ac, av))
	{
		free_all(&ctx);
		write(2, "Error\n", 6);
		return (1);
	}
	ctx.disorder = compute_disorder(ctx.a);
	run_strategy(&ctx);
	if (ctx.bench)
		print_bench(&ctx);
	free_all(&ctx);
	return (0);
}
