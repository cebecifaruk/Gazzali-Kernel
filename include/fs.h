#ifndef __VFS_H
#define __VFS_H

#define MAX_MOUNTPOINT 4

#include "Gazzali.h"
#define PATH_SEPARATOR '/'

#define FS_FILE        	0x0
#define FS_DIRECTORY   	0x1
#define FS_CHARDEVICE  	0x2
#define FS_BLOCKDEVICE 	0x3
#define FS_PIPE        	0x4
#define FS_SYMLINK     	0x5
#define FS_HARDLINK		0x6
#define FS_MOUNTPOINT  	0x7

typedef unsigned short 	ssize_t;
typedef unsigned int 	loff_t;
typedef unsigned int 	off_t;
typedef unsigned int 	mode_t;
typedef unsigned int	filldir_t;
typedef struct { uint16_t major, minor; } dev_t;


struct deviceNode {
	uint16_t 				major;
	struct fileOperations 	*f_op;
	struct deviceNode 		*prev,*next;	
};


struct file {
	mode_t 					f_mode;
	loff_t 					f_pos,f_count;
	unsigned short 			f_flags;
	dev_t					f_dev;
	unsigned long 			f_reada, f_ramax, f_raend, f_ralen, f_rawin;
	struct file 			*f_next, *f_prev,*f_system;
	int 					f_owner;         /* pid or -pgrp where SIGIO should be sent */
//	struct inode 			*f_inode;
	struct fileOperations 	*f_op;
//	unsigned long 			f_versioni;
	void 					*private_data;  /* needed for tty driver, and maybe others */

};

struct dentry {
	int						d_mounted;    /* is this a mount point? */
	void					*d_fsdata;    /* filesystem-specific data */
	long					d_ino;
	off_t					d_off;
	unsigned short			d_namelen;
	char					d_name[256]; /* short name */
};


struct dentryOperations {
	int				(*walk)			(struct file *, struct dentry *);
	int 			(*create) 		(struct file *, struct dentry *, int);
	struct dentry*	(*lookup) 		(struct file *, struct dentry *);
	int 			(*link) 		(struct file *, struct dentry *, struct dentry *);
	int 			(*unlink) 		(struct file *, struct dentry *);
	int 			(*symlink) 		(struct file *, struct dentry *, const char *);
	int 			(*mkdir) 		(struct file *, struct dentry *, int);
	int 			(*rmdir) 		(struct file *, struct dentry *);
	int 			(*mknod) 		(struct file *, struct dentry *, int, dev_t);
	int 			(*rename) 		(struct file *, struct dentry *, struct dentry *);
	int 			(*readlink) 	(struct file *, struct dentry *, char *, int);
//	int 			(*follow_link) 	(struct file *, struct dentry *, struct nameidata *);
//	int 			(*put_link) 	(struct file *, struct dentry *, struct nameidata *);
//	void 			(*truncate) 	(struct file *, struct dentry *);
	int 			(*permission) 	(struct file *, struct dentry *, int);
//	int 			(*setattr) 		(struct file *, struct dentry *, struct iattr *);
//	int 			(*getattr) 		(struct file *, struct vfsmount *, struct dentry *, struct kstat *);
//	int 			(*setxattr) 	(struct file *, struct dentry *, const char *,const void *, size_t, int);
//	ssize_t 		(*getxattr) 	(struct file *, struct dentry *, const char *, void *, size_t);
//	ssize_t 		(*listxattr) 	(struct file *, struct dentry *, char *, size_t);
//	int 			(*removexattr) 	(struct file *, struct dentry *, const char *);
};

struct fileOperations {
	int (*lseek) 	(struct file *, off_t, int);
	int (*read) 	(struct file *, char *, size_t);
	int (*write) 	(struct file *, const char *, size_t);
	int (*readdir) 	(struct file *, void *, filldir_t);
	int (*ioctl) 	(struct file *, unsigned int, unsigned long);
	int (*open) 	(struct file *);
	void(*release) 	(struct file *);
	int (*fsync) 	(struct file *);
	int (*fasync)	(struct file *, int);
	int (*check_media_change) 	(dev_t dev);
	int (*revalidate) 			(dev_t dev);
//	int (*select) 	(struct file *, int, select_table *);
//	int (*mmap) 	(struct file *, struct vm_area_struct *);
	struct dentryOperations *d_op;
};


/*      Device Functions        */
void 			vfs_init();
struct file 	*dev_open(dev_t);
int 			dev_register(uint16_t , struct fileOperations *);
int				dev_cleanup(uint16_t);

/*		System Call Directives	*/

#define SEEK_SET	0

/*		VFS System Calls		*/
int     sys_open	(const char *, int, int);
int     sys_write	(unsigned int, const void *, size_t);
int     sys_read	(unsigned int, void *, size_t);
int     sys_close	(unsigned int);
int     sys_lseek	(unsigned int, off_t, int);

int     sys_create	(const char *);
int     sys_mkdir	(const char *);
int     sys_rmdir	(const char *);
int     sys_rename 	(const char *, const char *);
int		sys_readdir	(unsigned int, struct dentry *, unsigned int);
int		sys_chdir	(const char *);

int     sys_chmod  	(const char *, int);
int     sys_mknod  	(const char *, int, unsigned int);

int     sys_mount  	(char *, char *, char *, unsigned long, void *);
int     sys_umount	(char *, int);

#endif
