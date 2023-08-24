#include "monty.h"

/**
 * handle_pchar - handles the pchar opcode which prints the ascii
 * value of the top element's value
 * @obj: the shared object
 * @err_msg: error message to print
 */
void handle_pchar(sharedobj_t *obj, const char *err_msg)
{
	if (stack_len(*obj->current_stack) < 1)
		get_out(obj, err_msg);

	if ((*obj->current_stack)->n > 127)
		get_out(obj, "L%d: can't pchar, value out of range\n");
}
