#include "push_swap.h"

static int	str_eq(const char *s1, const char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 == *s2);
}

/* Returns 1 if `arg` was a flag (and applies it), 0 if it is not a flag. */
static int	parse_flag(t_ctx *ctx, const char *arg)
{
	if (str_eq(arg, "--simple"))
		ctx->strat = STRAT_SIMPLE;
	else if (str_eq(arg, "--medium"))
		ctx->strat = STRAT_MEDIUM;
	else if (str_eq(arg, "--complex"))
		ctx->strat = STRAT_COMPLEX;
	else if (str_eq(arg, "--adaptive"))
		ctx->strat = STRAT_ADAPTIVE;
	else if (str_eq(arg, "--bench"))
		ctx->bench = 1;
	else
		return (0);
	return (1);
}

/* TODO: strict int parser. Must reject: "", "+", "-", "1a", " 1", overflow
** past INT_MIN/INT_MAX (careful: do NOT detect overflow after it happened).
** Returns 1 on success and writes to *out. */
static int	parse_int(const char *s, int *out)
{
	(void)s;
	(void)out;
	return (0);
}

/* Flags can appear anywhere. Everything else must be a valid int.
** Must also: reject duplicates, build ctx->a in argument order (first arg =
** top), set ctx->size_a, then call normalize(ctx).
** Returns 0 on ANY error (caller frees and prints "Error\n" on stderr). */
int	parse_args(t_ctx *ctx, int ac, char **av)
{
	int	i;
	int	value;

	i = 1;
	while (i < ac)
	{
		if (!parse_flag(ctx, av[i]))
		{
			if (!parse_int(av[i], &value))
				return (0);
			/* TODO: duplicate check + append node to ctx->a */
		}
		i++;
	}
	normalize(ctx);
	return (1);
}
