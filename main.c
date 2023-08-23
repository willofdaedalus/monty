#include "monty.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	FILE *file;
	int i = 0;
	int line_num = 1;
	char cur_line[100];
	char *file_path = NULL;
	char *words[MAX_WORDS];
	stack_t *head = NULL;

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
		exit(EXIT_FAILURE);
	}

	while (fgets(cur_line, sizeof(cur_line), file))
	{
		tokenize_line(cur_line, words);

		if (words[i])
		{
			init_opcode_check(&head, words, line_num, file);
			line_num++;
		}
		else
			continue;

		i = 0;
	}

	fclose(file);

	return (0);
}
