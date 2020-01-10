#include "Gazzali.h"

//extern
const uint8_t _binary_initrd_img_start[];

static int write (struct file *file, const char *buf, size_t count)
{
	memcpy((void *)(file->f_count + file->f_pos), buf, count);
	file->f_count += count;
	return 0;	
}

static int read(struct file *file, char *buf, size_t count)
{
	memcpy(buf, (void *)(file->f_count + file->f_pos), count);
	file->f_count += count;
	return 0;
}

static int open (struct file *file)
{
	file->f_count=0;
	file->f_pos=_binary_initrd_img_start;
	return 0;
}
//static
struct fileOperations initrd = {
	.open=open,
	.read=read,
	.write=write
};

