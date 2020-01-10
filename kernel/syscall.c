#include "Gazzali.h"

void sys_init()
{
        unsigned int i;
        for(i=0;i<SYSVECTOR_SIZE;i++)sysVector[i]=sys_noCall;
}

int sys_register(unsigned int syscallnum,void *syscall)
{
    sysVector[syscallnum]=syscall;
    return 0;
}

void sys_noCall()
{
        return;
}
