#include "push_swap.h"

/* disorder = inversions / total_pairs, in [0, 1].
** Spec pseudocode is O(n^2); fine, it runs once before any move.
** TODO: handle size < 2 (no pairs -> disorder 0, avoid dividing by zero). */
double	compute_disorder(t_node *a)
{
	(void)a;
	return (0.0);
}
