#ifndef MONTY_H
#define MONTY_H

#include <stddef.h>
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


/**
 * struct sharedobj_s - a bunch of properties I found
 * myself tossing in between functions so I figured I put them
 * in one
 * @words: the tokenised list of words on the current line
 * @file: the current file we're reading from
 * @line_num: the current line's number in the file
 * @current_stack: a pointer to pointer of the current stack
 */
typedef struct sharedobj_s
{
	char *words[MAX_WORDS];
	FILE *file;
	unsigned int line_num;
	stack_t **current_stack;
} sharedobj_t;

/* STACK OPERATIONS */
void push(stack_t **stack, unsigned int line_number);
void pall(stack_t **stack, unsigned int line_number);
void pint(stack_t **stack, unsigned int line_number);
void pop(stack_t **stack, unsigned int line_number);
void swap(stack_t **stack, unsigned int line_number);
void add(stack_t **stack, unsigned int line_number);
size_t stack_len(stack_t *stack);
void free_stack(stack_t *stack);


/* HELPER FUNCTIONS */
void init_opcode_check(sharedobj_t *obj);
void opcode_err_check(sharedobj_t *obj);
void tokenize_line(char *line, char **words);
void get_out(sharedobj_t *obj, char *message);
void processing_core(sharedobj_t **obj, FILE *file, stack_t **head);

#endif /* MONTY_H */
