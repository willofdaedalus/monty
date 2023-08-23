#include "monty.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int pushval = 0;

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
			if (strcmp(words[0], "push") == 0)
			{
				pushval = atoi(words[1]);
			}

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

void free_words(char **words)
{
	if (!words)
		return;

	while (*words)
	{
		printf("freeing %s\n", *words);
		free(*words);
		words++;
	}
}
