#include "Gazzali.h"

void rootProcess();
void kernel_main();

int kmain(void)
{
  //SystemInit();
  kernel_main();
  //sys_init();
  //vfs_init();
  //__initKernel(rootProcess,16);
	while(1);
}

void rootProcess()
{
  //sys_execve("/usr/bin/test.elf",NULL,NULL);
	while(1);
}
