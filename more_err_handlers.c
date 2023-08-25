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
		get_out(obj, err_msg);

	ch = (*obj->current_stack)->n;
	if (ch < 0 || ch > 127)
		get_out(obj, "L%d: can't pchar, value out of range\n");
}

