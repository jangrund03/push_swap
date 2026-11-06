#include "push_swap.h"

/* O(n^2): e.g. selection sort. Repeatedly bring the smallest remaining
** index to the top of a (pick ra or rra, whichever is shorter), pb it,
** then pa everything back. Use ctx->a[*].index, not .value. */
void	sort_simple(t_ctx *ctx)
{
	(void)ctx;
}
