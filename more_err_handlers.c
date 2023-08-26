#include "monty.h"

/**
 * handle_pchar - handles the pchar opcode which prints the ascii
 * value of the top element's value
 * @obj: the shared object
 * @err_msg: error message to print
 */
void handle_pchar(sharedobj_t *obj, const char *err_msg)
{
	int ch = 0;

	if (stack_len(*obj->current_stack) < 1)
		clean_up(obj, err_msg);

	ch = (*obj->current_stack)->n;
	if (ch < 0 || ch > 127) /* check if the char is in ascii map range */
		clean_up(obj, "L%d: can't pchar, value out of range\n");
}

