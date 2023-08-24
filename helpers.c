#include "monty.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int pushval = 0;

/**
 * processing_core - processing each line of file
 * @obj: the shared obj that sets everything off
 * @file: the file to read; here so we can free in main
 * @head: the new stack; here so we can free in main
 */
void processing_core(sharedobj_t **obj, FILE *file, stack_t **head)
{
	char cur_line[100];
	int line_num = 1, i = 0;

	while (fgets(cur_line, sizeof(cur_line), file))
	{
		tokenize_line(cur_line, (*obj)->words);

		(*obj)->current_stack = head;
		(*obj)->file = file;
		(*obj)->line_num = line_num;

		if ((*obj)->words[i])
		{
			init_opcode_check(*obj);
			line_num++;
		}
		else
		{
			/**
			 * update the line number count in order to give
			 * the right line number for the error!
			 */
			line_num++;
			continue;
		}
		i = 0;
	}
}

/**
 * init_opcode_check - checks the tokens against the allowed list of opcodes
 * @obj: this struct contains common elements shared across many functions
 */
void init_opcode_check(sharedobj_t *obj)
{
	int len = 0;
	int i = 0;

	instruction_t codes[] = {
		{ "push", push },
		{ "pall", pall },
		{ "pint", pint },
		{ "pop", pop },
		{ "swap", swap },
		{ "add", add },
	};

	len = sizeof(codes) / sizeof(codes[0]);
	while (i < len)
	{
		if (strcmp(obj->words[0], codes[i].opcode) == 0)
		{
			opcode_err_check(obj);
			codes[i].f(obj->current_stack, obj->line_num);
			return; /* not break otherwise the unknown instruction line runs */
		}

		i++;
	}
	if (i >= len)
	{
		fprintf(stderr, "L%d: unknown instruction %s\n",
				obj->line_num, obj->words[0]);
		free_stack(*(obj->current_stack));
		fclose(obj->file); /* close the file upon encountering an error */
		free(obj);
		exit(EXIT_FAILURE);
	}
}

/**
 * handle_opcode_proc - handles edge cases for values that need it like push
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
		{ "pint", handle_empty_stack, "L%d: can't pint, stack empty\n" },
		{ "pop", handle_empty_stack, "L%d: can't pop an empty stack\n" },
		{ "swap", handle_short_stack, "L%d: can't swap, stack too short\n" },
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
	if (obj->words[1])
		pushval = atoi(obj->words[1]);
	else
		get_out(obj, err_msg);
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
		get_out(obj, err_msg);
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
		get_out(obj, err_msg);
}

/**
 * get_out - gracefully exits upon encountering an error by freeing
 * memory that has been allocated and printing an error message
 * @obj: the shared obj handling data that most variables need
 */
void get_out(sharedobj_t *obj, const char *message)
{
	fprintf(stderr, message, obj->line_num);
	free_stack(*(obj->current_stack));
	fclose(obj->file); /* close the file upon encountering an error */
	free(obj);
	exit(EXIT_FAILURE);
}

/**
 * tokenize_line - splits the words in the current line
 * @line: the current line as a string
 * @words: the storage for the tokens
 */
void tokenize_line(char *line, char **words)
{
	int i = 0;
	char *token = NULL;
	char *delims = " \n\t$;";

	token = strtok(line, delims);
	while (token)
	{
		words[i] = token;
		token = strtok(NULL, delims);
		i++;
	}
	words[i] = NULL;
}
