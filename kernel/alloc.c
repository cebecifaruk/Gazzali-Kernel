#include "Gazzali.h"

#define ALLOC_SIZE 2048

static char mem[ALLOC_SIZE];

void *lastPointer = mem;

void *malloc (size_t Size)
{
    lastPointer+= Size;
	return lastPointer-Size;
}
int free(void *ptr)
{
	return 1;
}

