#include "push_swap.h"

/* Dispatch on ctx->disorder (computed BEFORE any move):
**   < 0.2        -> must be O(n^2)
**   0.2 .. < 0.5 -> must be O(n*sqrt(n))
**   >= 0.5       -> must be O(n log n)
** Your "internal technique" per regime is free (it need not be the same
** function as --simple/--medium/--complex, just in the right class).
** Document thresholds + rationale + complexity argument in the README.
** TODO: record which method ran so print_bench can report it. */
void	sort_adaptive(t_ctx *ctx)
{
	(void)ctx;
}
