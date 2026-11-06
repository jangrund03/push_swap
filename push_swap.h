#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>

/* The 11 push_swap operations. Order matters: it indexes ops_count[]
** and op_names[]. */
typedef enum e_op
{
	OP_SA,
	OP_SB,
	OP_SS,
	OP_PA,
	OP_PB,
	OP_RA,
	OP_RB,
	OP_RR,
	OP_RRA,
	OP_RRB,
	OP_RRR,
	OP_COUNT
}	t_op;

typedef enum e_strat
{
	STRAT_ADAPTIVE,
	STRAT_SIMPLE,
	STRAT_MEDIUM,
	STRAT_COMPLEX
}	t_strat;

/* One stack element. `index` = rank of value in the sorted input (0..n-1),
** filled by normalize(). Algorithms should work on `index`, not `value`. */
typedef struct s_node
{
	int				value;
	int				index;
	struct s_node	*next;
}	t_node;

/* Everything the program needs, passed around instead of globals
** (global variables are forbidden). */
typedef struct s_ctx
{
	t_node	*a;
	t_node	*b;
	size_t	size_a;
	size_t	size_b;
	t_strat	strat;
	int		bench;
	double	disorder;
	size_t	ops_count[OP_COUNT];
}	t_ctx;

/* parse.c */
int		parse_args(t_ctx *ctx, int ac, char **av);

/* stack.c -- raw stack primitives, NO printing, NO counting */
t_node	*stack_new(int value);
void	stack_add_back(t_node **stack, t_node *node);
void	stack_clear(t_node **stack);
void	stack_swap(t_node **stack);
void	stack_push(t_node **dst, t_node **src);
void	stack_rotate(t_node **stack);
void	stack_rrotate(t_node **stack);
void	normalize(t_ctx *ctx);

/* ops.c -- the ONLY place algorithms should call: prints + counts */
void	do_op(t_ctx *ctx, t_op op);

/* disorder.c */
double	compute_disorder(t_node *a);

/* bench.c */
void	print_bench(t_ctx *ctx);

/* strategies: each must sort ctx->a using only do_op() */
void	sort_simple(t_ctx *ctx);
void	sort_medium(t_ctx *ctx);
void	sort_complex(t_ctx *ctx);
void	sort_adaptive(t_ctx *ctx);

#endif
