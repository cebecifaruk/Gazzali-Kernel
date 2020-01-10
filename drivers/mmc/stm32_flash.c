#include "Gazzali.h"

static int read(struct file *file, char *buf, int count)
{
	memcpy(buf, (void *)(file->f_count + file->f_pos), count);
	file->f_count += count;
	return 0;
}

static int open (struct file *file)
{
	file->f_count=0;
	file->f_pos=0x08020000;
	return 0;
}
//static
struct fileOperations stm32_flash = {
	.open=open,
	.read=read
};

