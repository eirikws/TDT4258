#Chapter 3
##The Design
* capabilities(mechanism)
* abstraction on top of memory
* types of devices and their interfaces & implementation
  * global and persistent
  * fifo: block and unblock, with /without interrupt
  * single,priv,uid,wuid(wait uid)

##Major and Minor Numbers
* *__/dev__* directory
* major number: driver - device association (driver number)
* minor number: referred the exact device (device number)

##The Internal Representation of Device Numbers
* the``` dev_t``` type (defined in``` <linux/types.h>```) is used to hold device numbers—both the major and minor parts.
* obtain major and minor parts of dev_t:
``` c
#include<linux/kdev_t.h>
MAJOR(dev_t dev);
MINOR(dev_t dev);
```
* obtain dev_t from major and minor:
``` c
MKDEV(int major, int minor);
```

##Allocating and Freeing Device Numbers (Minor Numbers)
* statically-allocated device numbers
``` c
#include<linux/fs.h>
int register_chrdev_region(dev_t first, unsigned int count,
                           char *name);
```
  * first: often 0
  * count: request range, should be less than 20 bit integer
  * name: associated with device number, will appear in *__/proc/devices__* and *__sysfs__*
  * return: 0 - success; negative - error code

* dynamicly-allocated device numbers
``` c
#include<linux/fs.h>
int alloc_chrdev_region(dev_t *dev, unsigned int firstminor,
                        unsigned int count, char *name);
```
  * firstminor: often 0
  * count: request range, should be less than 20 bit integer
  * name: associated with device number, will appear in *__/proc/devices__* and *__sysfs__*
  * return: 0 - success; negative - error code
  * **dev : an output-only parameter** that will, on successful completion, hold the first number in your allocated range

*  Freeing: placed in module’s cleanup function
``` c
void unregister_chrdev_region(dev_t first, unsigned int count);
```

## Allocation of Major Numbers
* statically: most common ones in *__Documentation/devices.txt__*, picked an unused one;
* Dynamically: ```alloc_chrdev_region``` rather than ```register_chrdev_region```
  * blablabla


##File Operations
``` c
#include <linux/fs.h>
struct file_operations {
	struct module *owner;
	/*
	a pointer to the module that “owns” the structure. This field is used to prevent 
	the module from
	being unloaded while its operations are in use. Almost all the time, it is simply
	initialized to THIS_MODULE , a macro defined in <linux/module.h>
	*/
	loff_t (*llseek) (struct file *, loff_t, int);
	ssize_t (*read) (struct file *, char __user *, size_t, loff_t *);
	ssize_t (*write) (struct file *, const char __user *, size_t, loff_t *);
	ssize_t (*aio_read) (struct kiocb *, const struct iovec *, unsigned long, loff_t);
	ssize_t (*aio_write) (struct kiocb *, const struct iovec *, unsigned long, loff_t);
	int (*readdir) (struct file *, void *, filldir_t);
	unsigned int (*poll) (struct file *, struct poll_table_struct *);
	long (*unlocked_ioctl) (struct file *, unsigned int, unsigned long);
	long (*compat_ioctl) (struct file *, unsigned int, unsigned long);
	int (*mmap) (struct file *, struct vm_area_struct *);
	int (*open) (struct inode *, struct file *);
	int (*flush) (struct file *, fl_owner_t id);
	int (*release) (struct inode *, struct file *);
	int (*fsync) (struct file *, loff_t, loff_t, int datasync);
	int (*aio_fsync) (struct kiocb *, int datasync);
	int (*fasync) (int, struct file *, int);
	int (*lock) (struct file *, int, struct file_lock *);
	ssize_t (*sendpage) (struct file *, struct page *, int, size_t, loff_t *, int);
	unsigned long (*get_unmapped_area)(struct file *, unsigned long, unsigned long, unsigned long, unsigned long);
	int (*check_flags)(int);
	int (*flock) (struct file *, int, struct file_lock *);
	ssize_t (*splice_write)(struct pipe_inode_info *, struct file *, loff_t *, size_t, unsigned int);
	ssize_t (*splice_read)(struct file *, loff_t *, struct pipe_inode_info *, size_t, unsigned int);
	int (*setlease)(struct file *, long, struct file_lock **);
	long (*fallocate)(struct file *file, int mode, loff_t offset,
			  loff_t len);
	int (*show_fdinfo)(struct seq_file *m, struct file *f);
};

```
## File Structure ( never appears in userspace, has nothing to do with the FILE * in c library )
* representation of an open file in kernel space
* passed to correspondent operation by kernel, maintained until last instance closed
* after all of the file are closed, kerenl release the data structure
* "file pointer" *__filp__*
``` c
#include <linux/fs.h>
struct file {
  mode_t f_mode;/* FMODE_READ FMODE_WRITE  permissions*/
  loff_t f_pos;
  unsigned short f_flags; /* O_RONLY(seldom use, prefer f_mode), O_NONBLOCK, O_SYNC */
  unsigned short f_count;
  unsigned long f_reada, f_ramax, f_raend, f_ralen, f_rawin;
  struct file *f_next, *f_prev;
  int f_owner;         /* pid or -pgrp where SIGIO should be sent */
  struct inode * f_inode;
  struct file_operations * f_op;
  unsigned long f_version;
  void *private_data;  /* needed for tty driver, and maybe others */
};
```
* f_flags defined in ``` <linux/fcntl.h> ```

##The inode Structure
