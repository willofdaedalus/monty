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

/**
 * nop - opcode that does nothing
 * @stack: current stack
 * @line_number: current line number
 */
void nop(stack_t **stack, unsigned int line_number)
{
	(void) stack;
	(void) line_number;
}

/**
 * sub - opcode to subtract first node from second
 * @stack: the current stack
 * @line_number: the line number
 */
void sub(stack_t **stack, unsigned int line_number)
{
	int result = 0;

	(void)line_number;
	result = (*stack)->next->n - (*stack)->n;
	pop(stack, line_number);
	(*stack)->n = result;
}

/**
 * div - divides the second top element by the top element
 * @stack: the current stack
 * @line_number: the line number
 */
void divide(stack_t **stack, unsigned int line_number)
{
	int result = 0;

	(void)line_number;
	result = (*stack)->next->n / (*stack)->n;
	pop(stack, line_number);
	(*stack)->n = result;

}
