#include "push_swap.h"

t_node	*stack_new(int value)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->value = value;
	node->index = 0;
	node->next = NULL;
	return (node);
}

void	stack_add_back(t_node **stack, t_node *node)
{
	t_node	*cur;

	if (!*stack)
	{
		*stack = node;
		return ;
	}
	cur = *stack;
	while (cur->next)
		cur = cur->next;
	cur->next = node;
}

void	stack_clear(t_node **stack)
{
	t_node	*next;

	while (*stack)
	{
		next = (*stack)->next;
		free(*stack);
		*stack = next;
	}
}
