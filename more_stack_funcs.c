/**
 * This file exists because the style guide dictates there should be
 * a maximum of five functions per file
 */

#include "monty.h"

/**
 * swap - opcode to swap the top two variables
 * @stack: the current stack
 * @line_number: again not used but it's still here
 */
void swap(stack_t **stack, unsigned int line_number)
{
	stack_t *top = *stack;
	int tmp = 0;

	(void)line_number;
	tmp = top->n;
	top->n = top->next->n;
	top->next->n = tmp;
}
