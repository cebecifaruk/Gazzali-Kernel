#include "Gazzali.h"

void __initKernel(void *Task,size_t StackSize)
{
    iterProcess= (Process *) malloc(StackSize + sizeof(Process) + ARCH_SIZEOF_REGISTERS) + StackSize + ARCH_SIZEOF_REGISTERS;
    
	iterProcess->sp=__schedulerInitStack(Task,iterProcess);
    iterProcess->sp_end= iterProcess - StackSize - ARCH_SIZEOF_REGISTERS;

	memset(iterProcess->fd, 0x00, sizeof(struct fd)*MAX_FD);
	iterProcess->pid=0;
    iterProcess->status=0;
    iterProcess->next=NULL;
    lastProcess=iterProcess;
    OS_Start(iterProcess->sp);
}

pid_t __addProcess (void *Task,size_t StackSize)
{
    Process *NewTask = (Process *) malloc(StackSize + sizeof(Process) + ARCH_SIZEOF_REGISTERS) + StackSize + ARCH_SIZEOF_REGISTERS;
	NewTask->sp=__schedulerInitStack(Task,NewTask);
    NewTask->sp_end= NewTask - StackSize - ARCH_SIZEOF_REGISTERS;
    NewTask->pid=1;
    NewTask->status=0;
    NewTask->next=NULL;
	unsigned int i;for(i=0;i<MAX_FD;i++)NewTask->fd[i].file=NULL;
    lastProcess->next=NewTask;
    lastProcess=NewTask;
    return NewTask->pid;
}

void __exit()
{
    iterProcess->status=1;
    SysTick_Handler();
}


void *__scheduler(void* currentSP)
{
    //Backup Stack
    iterProcess->sp=currentSP;

    //Is task finished
    if (iterProcess->status == 0) {
        //Add Queue
        if(iterProcess->next != NULL) {
            lastProcess->next=iterProcess;
            lastProcess=iterProcess;
        }
        //Wait finish function
        else return iterProcess->sp;
    }
    else if (iterProcess->next==NULL ) while(1);

    iterProcess=iterProcess->next;
    lastProcess->next=NULL;
    return iterProcess->sp;
}
