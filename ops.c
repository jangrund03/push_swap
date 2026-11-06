#include "push_swap.h"

static const char	*g_names[OP_COUNT] = {"sa", "sb", "ss", "pa", "pb", "ra",
	"rb", "rr", "rra", "rrb", "rrr"};

/* TODO: replace this global-free-but-stringy table lookup if the Norm
** complains about the static array; a switch returning literals also works.
** (File-scope `static const` is generally fine; global *variables* are not.)
*/
static void	apply(t_ctx *c, t_op op)
{
	if (op == OP_SA || op == OP_SS)
		stack_swap(&c->a);
	if (op == OP_SB || op == OP_SS)
		stack_swap(&c->b);
	if (op == OP_PA)
		stack_push(&c->a, &c->b);
	if (op == OP_PB)
		stack_push(&c->b, &c->a);
	if (op == OP_RA || op == OP_RR)
		stack_rotate(&c->a);
	if (op == OP_RB || op == OP_RR)
		stack_rotate(&c->b);
	if (op == OP_RRA || op == OP_RRR)
		stack_rrotate(&c->a);
	if (op == OP_RRB || op == OP_RRR)
		stack_rrotate(&c->b);
}

/* TODO: keep size_a / size_b correct for pa and pb (and only when the push
** is not a no-op). Fix when you flesh out stack_push. */
void	do_op(t_ctx *ctx, t_op op)
{
	size_t	len;

	apply(ctx, op);
	ctx->ops_count[op]++;
	len = 0;
	while (g_names[op][len])
		len++;
	write(1, g_names[op], len);
	write(1, "\n", 1);
}
