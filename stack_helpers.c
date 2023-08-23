#include "monty.h"
#include <stdio.h>
#include <stdlib.h>


/**
 * push - opcode to push a value on to the stack
 * @stack: the current stack for monty
 * @line_number: the current line number
 */
void push(stack_t **stack, unsigned int line_number)
{
	stack_t *head = *stack;
	stack_t *node = NULL;

	(void)line_number;
	node = malloc(sizeof(stack_t));
	if (!node)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}

	node->n = pushval;
	node->next = head;
	node->prev = NULL;

	if (head)
		head->prev = node;

	head = node;
	*stack = head;
}

/**
 * pall - opcode to print all elements on the stack
 * @stack: the current stack for monty
 * @line_number: the current line number
 */
void pall(stack_t **stack, unsigned int line_number)
{
	stack_t *head = NULL;

	(void)line_number;
	if (!(*stack))
		return;

	head = *stack;
	while (head)
	{
		printf("%d\n", head->n);
		head = head->next;
	}
}

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
