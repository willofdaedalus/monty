#include "monty.h"
#include <stdio.h>


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

/**
 * pchar - prints the character associated with the value at the top
 * of the stack
 * @stack: the current stack
 * @line_number: the line number
 */
void pchar(stack_t **stack, unsigned int line_number)
{
	(void)line_number;

	printf("%c\n", (*stack)->n);
}

/**
 * pstr - prints from top to bottom the ascii values of
 * each element's value
 * @stack: the current stack
 * @line_number: the current line number
 */
void pstr(stack_t **stack, unsigned int line_number)
{
	stack_t *head = NULL;
	int ch = 0;

	(void)line_number;

	if (!(*stack))
		putchar('\n');

	head = *stack;
	while (head)
	{
		ch = head->n;
		if (ch > 0 && ch < 128)
			putchar(ch);
		else
			break;

		head = head->next;
	}
	putchar('\n');
}
