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

		/* hand over the necessary details to sharedobj */
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

	/* opcodes and their associated functions */
	instruction_t codes[] = {
		{ "push", push }, { "pall", pall }, { "pint", pint },
		{ "pop", pop }, { "swap", swap }, { "add", add },
		{ "nop", nop }, { "sub", sub }, { "div", divide },
		{ "mul", mul }, { "mod", mod }, { "#", nop },
		{ "pchar", pchar }, { "pstr", pstr },
	};

	len = sizeof(codes) / sizeof(codes[0]); /* compute size of array */
	while (i < len)
	{
		if (obj->words[0][0] == '#')
			return;

		if (strcmp(obj->words[0], codes[i].opcode) == 0)
		{
			opcode_err_check(obj);
			codes[i].f(obj->current_stack, obj->line_num);
			return; /* not break otherwise the unknown instruction line runs */
		}

		i++;
	}

	/* 
	 * free the memory if the command is not found
	 * we can't use clean_up because this needs the instruction
	 * name in order to print
	 */
	fprintf(stderr, "L%d: unknown instruction %s\n",
			obj->line_num, obj->words[0]);
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

/**
 * clean_up - gracefully exits upon encountering an error by freeing
 * memory that has been allocated and printing an error message
 * @obj: the shared obj handling data that most variables need
 * @message: the message to print
 */
void clean_up(sharedobj_t *obj, const char *message)
{
	fprintf(stderr, message, obj->line_num);
	free_stack(*(obj->current_stack));
	fclose(obj->file); /* close the file upon encountering an error */
	free(obj);
	exit(EXIT_FAILURE);
}
