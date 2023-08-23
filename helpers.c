#include "monty.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int pushval = 0;

/**
 * init_opcode_check - checks the tokens against the allowed list of opcodes
 * @head: the head of the stack
 * @words: a tokenised list of words of the current line
 * @line_num: the current line number
 * @file: the FILE that is currently being read
 */
void init_opcode_check(stack_t **head, char **words, int line_num, FILE *file)
{
	int len = 0;
	int i = 0;

	instruction_t codes[] = {
		{ "push", push },
		{ "pall", pall },
	};

	(void)head;
	len = sizeof(codes) / sizeof(codes[0]);
	while (i < len)
	{
		if (strcmp(words[0], codes[i].opcode) == 0)
		{
			handle_opcode_proc(words, line_num, file, *head);
			codes[i].f(head, line_num);
			return;
		}

		i++;
	}
	if (i >= len)
	{
		fprintf(stderr, "L%d: unknown instruction %s\n", line_num, words[0]);
		fclose(file); /* close the file upon encountering an error */
		exit(EXIT_FAILURE);
	}
}

/**
 * handle_opcode_proc - handles edge cases for values that need it like push
 * @words: the tokenised list of words from the current line
 * @line_num: the current line number
 * @file: the current file open; useful for when a value fails so we free
 * @stack: the current stack
 */
void handle_opcode_proc(char **words, int line_num, FILE *file, stack_t *stack)
{
	if (strcmp(words[0], "push") == 0)
	{
		if (words[1])
			pushval = atoi(words[1]);
		else
		{
			fprintf(stderr, "L%d: usage: push integer\n", line_num);
			free_stack(stack);
			fclose(file); /* close the file upon encountering an error */
			exit(EXIT_FAILURE);
		}
	}
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
