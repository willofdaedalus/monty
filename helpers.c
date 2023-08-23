#include "monty.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void init_opcode_check(stack_t **head, char *opcode)
{
	int len = 0;
	int i = 0;

	instruction_t instructions[] = {
		{ "push", push },
		{ "pall", pall },
	};

	len = sizeof(instructions) / sizeof(instructions[0]);
	while (i < len)
	{
		if (strncpy(opcode, instructions[i].opcode, strlen(opcode)))
			instructions[i].f(head, 5);

		i++;
	}
}

void tokenize_line(char *line, char **words)
{
	int i = 0;
	char *token = NULL;

	token = strtok(line, " \t");
	while (token)
	{
		words[i] = token;
		token = strtok(NULL, " \t");
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
