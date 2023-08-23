#include "monty.h"
#include <stdlib.h>

/**
 * free_stack - frees memory for the stack
 * @stack: the stack to free
 */
void free_stack(stack_t *stack)
{
	stack_t *tmp = NULL;

	if (!stack)
		return;

	while (stack)
	{
		tmp = stack->next;
		free(stack);
		stack = tmp;
	}
}

/**
 * stack_len - prints the numbers of elements in the stack
 * @stack: the stack to check
 * Return: returns the number of elements in the stack
 */
size_t stack_len(stack_t *stack)
{
	size_t retval = 0;
	stack_t *tmp = NULL;

	if (stack)
	{
		tmp = stack;
		while (tmp)
		{
			retval++;
			tmp = tmp->next;
		}
	}

	return (retval);
}
