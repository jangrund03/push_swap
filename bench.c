#include "push_swap.h"

/* Everything here goes to stderr (fd 2), and only when --bench is set.
** Required output (see subject VI.5.1):
**   [bench] disorder: 49.93%          (two decimals)
**   [bench] strategy: Adaptive / O(n√n)
**   [bench] total_ops: 7997
**   [bench] sa: 0  sb: 0  ss: 0  pa: 500  pb: 500
**   [bench] ra: ..  rb: ..  rr: ..  rra: ..  rrb: ..  rrr: ..
** TODO: you need your own putnbr / putstr to fd 2 (or ft_printf with fd).
** TODO: for Adaptive, report which method was actually used + its class. */
void	print_bench(t_ctx *ctx)
{
	(void)ctx;
}
