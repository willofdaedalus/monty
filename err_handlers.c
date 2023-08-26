#include "monty.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

/**
 * opcode_err_check - handles edge cases for values that need it like push
 * @obj: this struct contains common elements shared across many functions
 */
void opcode_err_check(sharedobj_t *obj)
{
	int i = 0, arrlen = 0;

	/**
	 * store an array of each opcode and its associated function
	 * we then check the opcode from the textfile against our list
	 * of known opcodes to find its function
	 * there will always be a function because we handle unknow opcodes
	 * in the init_opcode_chec function
	 */
	error_map errors[] = {
		{ "push", handle_push, "L%d: usage: push integer\n" },
		{ "pchar", handle_pchar, "L%d: can't pchar, stack empty\n" },
		{ "mul", handle_short_stack, "L%d: can't mul, stack too short\n" },
		{ "pint", handle_empty_stack, "L%d: can't pint, stack empty\n" },
		{ "pop", handle_empty_stack, "L%d: can't pop an empty stack\n" },
		{ "swap", handle_short_stack, "L%d: can't swap, stack too short\n" },
		{ "add", handle_short_stack, "L%d: can't add, stack too short\n" },
		{ "sub", handle_short_stack, "L%d: can't sub, stack too short\n" },
		{ "div", handle_div, "L%d: can't div, stack too short\n" },
		{ "mod", handle_div, "L%d: can't mod, stack too short\n" },
	};

	arrlen = sizeof(errors) / sizeof(errors[0]);
	while (i < arrlen)
	{
		/* once opcode is found, execute the associated funtion */
		if (strcmp(obj->words[0], errors[i].opcode) == 0)
		{
			errors[i].f(obj, errors[i].err_msg);
			break;
		}
		i++;
	}
}

/**
 * handle_push - handles the push opcode; this is in a seperate function
 * because of how niche it is and its edge cases
 * @obj: the shared obj carrying all our properties
 * @err_msg: error message to print when the value fails
 */
void handle_push(sharedobj_t *obj, const char *err_msg)
{
	char *cur_word = obj->words[1];
	int i = 0;

	/**
	 * check each individual byte before doing atoi
	 * because atoi refuses to do error handling
	 */
	if (cur_word)
	{
		while (cur_word[i])
		{
			if (cur_word[i] != '-' && !isdigit(cur_word[i]))
				clean_up(obj, err_msg);
			i++;
		}
		pushval = atoi(obj->words[1]);
		return; /* early return so we don't trigger cleanup below */
	}
	clean_up(obj, err_msg);
}

/**
 * handle_div - handles the opcode for division
 * @obj: the shared obj
 * @err_msg: the standard error message
 */
void handle_div(sharedobj_t *obj, const char *err_msg)
{
	handle_short_stack(obj, err_msg);

	if ((*obj->current_stack)->n == 0)
		clean_up(obj, "L%d: division by zero\n");
}

/**
 * handle_empty_stack - handles opcodes that complain when the stack is
 * empty; useful for pint, pop etc
 * @obj: shared obj sharing properties
 * @err_msg: the error message to print
 */
void handle_empty_stack(sharedobj_t *obj, const char *err_msg)
{
	if (!*obj->current_stack)
		clean_up(obj, err_msg);
}

/**
 * handle_short_stack - handles opcodes that complain when the stack is
 * too short; useful for pint, pop etc
 * @obj: shared obj sharing properties
 * @err_msg: the error message to print
 */
void handle_short_stack(sharedobj_t *obj, const char *err_msg)
{
	if (stack_len(*obj->current_stack) < 2)
		clean_up(obj, err_msg);
}
