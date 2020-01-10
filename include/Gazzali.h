#ifndef GAZZALIKERNEL_H
#define GAZZALIKERNEL_H

#ifdef __cplusplus
extern "C" {
#endif

/*Kernel Parameters*/
#define MAX_TASK 4
#define MAX_FD  8

/*Kernel Includes*/
#include <stdint.h>		
#include "arch.h"
#include <stddef.h>
#include "libc.h"

#include "syscall.h"
#include "module.h"
#include "fs.h"
#include "exec.h"

/*Kernel Types*/
typedef uint16_t pid_t;
typedef uint16_t pstatus_t;

struct fd {
	struct file	*file;
	off_t		offset;
};

struct ProcessHeader
{
    pid_t       pid;
    pstatus_t   status;
    void        *sp_end;
    void        *sp;
    struct fd	fd[MAX_FD];        
    struct ProcessHeader *next;
};
typedef struct ProcessHeader Process;

Process		*iterProcess;
Process		*lastProcess;


/* Kernel Functions (start with kernel functions __)
 *
 * */


/*Scheduler & MultiProcess functions*/
void	*__scheduler	(void*);
void	__initKernel	(void *,size_t);
pid_t	__addProcess	(void *, size_t);
void	__deleteProcess	(pid_t);
void	__exit			();

void	*__schedulerInitStack(void *, void *);
void	OS_Start		(void *);
void	SysTick_Handler	(void);


#ifdef __cplusplus
}
#endif

#endif
