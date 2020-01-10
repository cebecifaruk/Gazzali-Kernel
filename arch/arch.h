#ifndef ARCH_H
#define ARCH_H

#include "Gazzali.h"


/* Application start address */

#define ARCH_SIZEOF_REGISTERS                    (16*4)
#define LITTLE_ENDIAN




unsigned int*       __archInitStack(unsigned int*,void *);
void                G_ArchInit(void);
unsigned int*       G_ArchContextSwitch(unsigned int *next);


#endif
