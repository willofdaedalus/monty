#include "monty.h"


/**
 * mod - computes the rest of the division of the second top
 * element of the stack by the top element of the stack.
 * @stack: the current stack
 * @line_number: the line number
 */
void mod(stack_t **stack, unsigned int line_number)
{
	int result = 0;

	(void)line_number;
	result = (*stack)->next->n % (*stack)->n;
	pop(stack, line_number);
	(*stack)->n = result;
}
