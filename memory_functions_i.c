#include "shell.h"

/**
* b_free - this function frees a pointer and NULLs the address
* @ptr: address of the pointer to be freed
*
* Return: 1 if freed, otherwise 0.
*/

int b_free(void **ptr)

{
if (ptr && *ptr)

{
free(*ptr);
*ptr = NULL;
return (1);
}

return (0);
}
