#ifndef __SYSCALL_H
#define __SYSCALL_H

#define SYS_CALL_NUM_MKDIR		61
#define SYS_CALL_NUM_RMDIR		62
#define SYS_CALL_NUM_RENAME		63

#define SYS_CALL_NUM_EXIT		1
#define SYS_CALL_NUM_FORK		2
#define SYS_CALL_NUM_READ		3
#define SYS_CALL_NUM_WRITE		4
#define SYS_CALL_NUM_OPEN		5
#define SYS_CALL_NUM_CLOSE		6
#define SYS_CALL_NUM_WAITPID	7
#define SYS_CALL_NUM_CREATE		8
#define SYS_CALL_NUM_LINK		9
#define SYS_CALL_NUM_UNLINK		10
#define SYS_CALL_NUM_EXECVE		11
#define SYS_CALL_NUM_CHDIR		12
#define SYS_CALL_NUM_TIME		13
#define SYS_CALL_NUM_MKNOD		14
#define SYS_CALL_NUM_CHMOD		15
#define SYS_CALL_NUM_LCHOWN		16

#define SYS_CALL_NUM_STAT		18
#define SYS_CALL_NUM_LSEEK		19
#define SYS_CALL_NUM_GETPID		20
#define SYS_CALL_NUM_MOUNT		21
#define SYS_CALL_NUM_UMOUNT		22
#define SYS_CALL_NUM_SETUID		23
#define SYS_CALL_NUM_GETUID		24


#define SYSVECTOR_SIZE 10

void    *sysVector[SYSVECTOR_SIZE];


void    sys_init();
int     sys_register(unsigned int, void *);
void    sys_noCall();

#endif
