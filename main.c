#include "monty.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * main - entry point
 * @argc: the arg count
 * @argv: the args list
 * Return: returns 0 for success
 */
int main(int argc, char **argv)
{
	FILE *file;
	char *file_path = NULL;
	stack_t *head = NULL;
	sharedobj_t *obj = malloc(sizeof(sharedobj_t));

	if (argc != 2)
	{
		printf("USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}

	file_path = argv[1];
	file = fopen(file_path, "r");
	if (!file)
	{
		fprintf(stderr, "Error: Can't open file %s\n", file_path);
		free(obj);
		exit(EXIT_FAILURE);
	}

	/* check here for main implementation details */
	processing_core(&obj, file, &head);

	fclose(file);
	free_stack(head);
	free(obj);

	return (0);
}
