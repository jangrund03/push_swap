#include "push_swap.h"

/* O(n*sqrt(n)): chunk-based. Roughly: push elements to b in ranges of
** ~sqrt(n) indices, then pull back max-first choosing the cheaper of
** rb/rrb. NOTE: random inputs have disorder ~0.5, so this strategy is hit
** by the 100/500-number benchmarks too -- it must perform, not just exist. */
void	sort_medium(t_ctx *ctx)
{
	(void)ctx;
}
