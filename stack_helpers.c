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
 * pint - opcode to print value at the top of the stack
 * @stack: the current stack for monty
 * @line_number: the current line number
 */
void pint(stack_t **stack, unsigned int line_number)
{
	/*
	 * HEADS UP; there's a reason why this function is only two lines
	 * and its because error handling and stack checking is not handled
	 * in here
	 * I know I know that's probably not for the best but
	 * I decided to consolidate them all in one function called
	 * handle_opcode_proc in the helpers.c file
	 * if you need to do any error handling for the operations
	 * check there!
	 */
	(void)line_number;
	printf("%d\n", (*stack)->n);
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
