#include "Gazzali.h"
#include "fs.h"

static struct deviceNode 	rootDevice;
static struct deviceNode 	*iterDevice;
static struct file			rootFile;
static struct file			*iterFile;
static struct file			*rootdir;

extern struct fileOperations initrd;

void vfs_init()
{
	//Reset values
	memset(&rootFile, 0x00, sizeof(struct file));
	memset(&rootDevice, 0x00, sizeof(struct deviceNode));
	
	// Device Node Init
	rootDevice.major = 0;
	rootDevice.f_op = NULL;
	rootDevice.next = NULL;
	rootDevice.prev = NULL;
	iterDevice = &rootDevice;
	
	//Root Filesystem device connection
	dev_register(8,&initrd);
	
	//TODO: root filesystem mounting
	dev_t dev = {.major=8,.minor=0};
	rootdir = malloc(sizeof(struct file));
	rootdir->f_system=dev_open(dev);
	
	extern struct fileOperations romfs;
	rootdir->f_op=(void *)&romfs;
	
	if (!rootdir) while(1);
	// Register System Calls
	sys_register(SYS_CALL_NUM_OPEN,sys_open);		
	sys_register(SYS_CALL_NUM_READ,sys_read);
	sys_register(SYS_CALL_NUM_WRITE,sys_write);
	sys_register(SYS_CALL_NUM_CLOSE,sys_close);
	sys_register(SYS_CALL_NUM_LSEEK,sys_lseek);
	sys_register(SYS_CALL_NUM_CREATE,sys_create);
	sys_register(SYS_CALL_NUM_MKDIR,sys_mkdir);
	sys_register(SYS_CALL_NUM_RMDIR,sys_rmdir);
	sys_register(SYS_CALL_NUM_RENAME,sys_rename);
	sys_register(SYS_CALL_NUM_CHMOD,sys_chmod);
	sys_register(SYS_CALL_NUM_MKNOD,sys_mknod);
	sys_register(SYS_CALL_NUM_MOUNT,sys_mount);
	sys_register(SYS_CALL_NUM_UMOUNT,sys_umount);

}


int dev_register (uint16_t major, struct fileOperations *operations)
{
	//TODO:Unsupported Function Detection
	
	//Register device node
	struct deviceNode * newDevice = malloc (sizeof(struct deviceNode));
	newDevice->next = NULL;
	newDevice->major = major;
	newDevice->f_op = operations;
	iterDevice->next = newDevice;
	newDevice->prev = iterDevice;
	iterDevice=newDevice;
	return 0;
}

int dev_cleanup (uint16_t major)
{
	struct deviceNode *iter;
	for (iter=&rootDevice;iter->major != major && iter->next ;iter=iter->next);
	if(iter->next) return -1;
	iter->prev->next=iter->next;
	free(iter);
	return 1;
}

struct file *dev_open(dev_t dev)
{
	struct file *device;
	for(device=&rootFile; device->f_dev.major==dev.major 
			&& device->f_dev.minor==dev.minor 
			&& device->f_next; device=device->f_next);
	
	//HATA VAR  vvvv
	if(!device->f_next && device) {
		struct deviceNode *iter;
		for(iter=&rootDevice;iter->major!=dev.major && iter->next;iter=iter->next);
		if (iter->major==dev.major) {
			device = malloc(sizeof(struct file));
			device->f_op = iter->f_op;
			device->f_dev = dev; 
			device->f_op->open(device);
			return device;
		}
		else return NULL;		
	}

	else return device;
}

//TODO: mount point detection
//TODO: /a/b///c//d Multiple sperator
int sys_open(const char *filename, int flags, int mode)
{
	struct file *device=rootdir;
	
	struct dentry dentry;
	dentry.d_off=0;

	int (*walk)(struct file *, struct dentry *);
	
	walk=device->f_op->d_op->walk;
	
	//Path Walking
	unsigned int i,n;
	for(i=0;filename[i];i++){
		if(filename[i]==PATH_SEPARATOR){
			for(n=0;filename[i+n+1]!=PATH_SEPARATOR && filename[i+n+1];n++);
			strncpy(dentry.d_name,filename+i+1,n);
			if(walk(device,&dentry))return -1;
			i+=n;
		}
	}
	struct file *file = malloc(sizeof(struct file));
	file->f_pos=dentry.d_off;
	file->f_op=device->f_op;
	file->f_system=rootdir->f_system;

	if (file == NULL)return -1;
	if (!file->f_op) return -1;
	if (file->f_op->open(file)){free(file);return -1;}
	
	// Put opened file (struct file *file) to fd
	for(i=0;i<MAX_FD && iterProcess->fd[i].file;i++);
	if(iterProcess->fd[i].file) return -1;
	iterProcess->fd[i].file=file;
	return i;
}

int sys_write(unsigned int fd, const void *buf,size_t count)
{
	if (!(iterProcess->fd[fd].file->f_op)) return -1;
	iterProcess->fd[fd].file->f_count=iterProcess->fd[fd].offset;
	int retval = iterProcess->fd[fd].file->f_op->write(iterProcess->fd[fd].file,buf,count);
	iterProcess->fd[fd].offset=iterProcess->fd[fd].file->f_count;
	return retval;
}

int sys_read(unsigned int fd, void *buf, size_t count)
{
	if (!(iterProcess->fd[fd].file->f_op)) return -1;
	iterProcess->fd[fd].file->f_count=iterProcess->fd[fd].offset;
	int retval = iterProcess->fd[fd].file->f_op->read(iterProcess->fd[fd].file,buf,count);
	iterProcess->fd[fd].offset=iterProcess->fd[fd].file->f_count;
	return retval;

}

int sys_close(unsigned int fd)
{
	free(iterProcess->fd[fd].file);
	iterProcess->fd[fd].file=NULL;
	return 1;
}

//TODO: Add SEEK_CUR SEEK_END support
int sys_lseek(unsigned int fd, off_t offset, int whence)
{
	iterProcess->fd[fd].offset=offset;
	return 0;
}

int sys_create(const char *pathname)
{
	return -1;
}

int sys_mkdir(const char *pathname)
{
	return -1;
}

int sys_rmdir(const char *pathname)
{
	return -1;
}

int sys_rename(const char *oldpath, const char *newpath)
{
	return-1;
}

int	sys_readdir(unsigned int fd, struct dentry *dentry, unsigned int count)
{
	return -1;
}

int	sys_chdir(const char *path)
{
	return -1;
}

int sys_chmod(const char *path, int mod)
{
	return -1;
}

int sys_mknod(const char *pathname, int a, unsigned int b)
{
	return -1;
}

int sys_mount(char * source, char *target, char *type, unsigned long flags, void * data)
{
	return -1;
}

int sys_umount(char *path, int flags)
{
	return -1;
}
