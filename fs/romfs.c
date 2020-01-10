#include "Gazzali.h" 

struct fileOperations romfs;

/*		ROMFS HEADER		*/
struct file_header {
	union{
		char 	magic[8];
		struct {
			uint32_t	next;
			uint32_t 	info;
		};
	};
	uint32_t 	size;
	uint32_t 	checksum;
	char 		name[16];
};

/*		ROMFS Filetypes			*/
enum {
	HARDLINK		=0,
	DIRECTORY		=1,
	REGULAR_FILE	=2,
	SYMBOLIC_LINK	=3,
	CHAR_DEVICE		=4,
	BLOCK_DEVICE	=5,
	SOCKET			=6,
	FIFO			=7
};


static int walk (struct file *file, struct dentry *dentry)
{
	// Goto child dir (new created dentry is a root dentry)
	struct file_header fhdr;
	if(dentry->d_off) {
		file->f_system->f_count=dentry->d_off;
		file->f_system->f_op->read(file->f_system,(char *)&fhdr,sizeof(struct file_header));
		fhdr.next=fhdr.info;
		//TODO: Is a dir
	}

	else fhdr.next=
#if	defined(LITTLE_ENDIAN)
	0x20000000;
#else
	0x20;
#endif
	uint32_t last;
	do{

#ifdef	LITTLE_ENDIAN
		fhdr.next=__bswap_32(fhdr.next);
#endif
		last=fhdr.next;
		file->f_system->f_count= 0xFFFFFFF0 & fhdr.next;
		if(!file->f_system->f_count) return -1;
		file->f_system->f_op->read(file->f_system,(char *)&fhdr,sizeof(struct file_header));
	}while(!strcmp(fhdr.name,dentry->d_name));
	
	//Update Dentry
	dentry->d_off = last& 0xFFFFFFF0;
	return 0;
}


static int open (struct file *file)
{
	file->f_pos += 0x20;
	return 0;
}

static int read (struct file *file, char *buf, size_t n)
{
	file->f_system->f_count= file->f_count + file->f_pos;
	int retval = file->f_system->f_op->read(file->f_system,buf,n);
	file->f_count = file->f_system->f_count - file->f_pos;
	return retval;
}

static struct dentryOperations d_romfs = {
	.walk=walk
};

struct fileOperations romfs = {
	.open=open,
	.read=read,
	.d_op = &d_romfs
};

void romfsinit ()
{
	
}
