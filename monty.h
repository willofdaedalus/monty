#ifndef MONTY_H
#define MONTY_H

#include <stdio.h>

#define MAX_WORDS 64
extern int pushval;


/**
 * struct stack_s - doubly linked list representation of a stack (or queue)
 * @n: integer
 * @prev: points to the previous element of the stack (or queue)
 * @next: points to the next element of the stack (or queue)
 *
 * Description: doubly linked list node structure
 * for stack, queues, LIFO, FIFO
 */
typedef struct stack_s
{
	int n;
	struct stack_s *prev;
	struct stack_s *next;
} stack_t;

/**
 * struct instruction_s - opcode and its function
 * @opcode: the opcode
 * @f: function to handle the opcode
 *
 * Description: opcode and its function
 * for stack, queues, LIFO, FIFO
 */
typedef struct instruction_s
{
	char *opcode;
	void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;

/* STACK OPERATIONS */
void push(stack_t **stack, unsigned int line_number);
void pall(stack_t **stack, unsigned int line_number);
void free_stack(stack_t *stack);


/* HELPER FUNCTIONS */
void init_opcode_check(stack_t **head, char **words, int line_num, FILE *file);
void handle_opcode_proc(char **words, int line_num, FILE *file, stack_t *stack);
void tokenize_line(char *line, char **words);

#endif /* MONTY_H */
