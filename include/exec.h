#ifndef __EXEC_H
#define __EXEC_H

int sys_execve(const char *filename, char *const argv[], char *const envp[]);

#endif
