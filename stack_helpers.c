#include "monty.h"
#include <stdio.h>
#include <stdlib.h>

/**
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

	node->n = STACK_VALUE;
	node->next = head;
	node->prev = NULL;

	if (head)
		head->prev = node;

	head = node;
	*stack = head;
}

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
*/
