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

## file_operations, file, inode
###File Operations
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
### File Structure ( never appears in userspace, has nothing to do with the FILE * in c library )
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

###The inode Structure
The VFS inode data structure holds information about a file or directory on disk.
``` c
struct inode {
    kdev_t                       i_dev;
    unsigned long                i_ino;
    umode_t                      i_mode;
    nlink_t                      i_nlink;
    uid_t                        i_uid;
    gid_t                        i_gid;
    kdev_t                       i_rdev;
    off_t                        i_size;
    time_t                       i_atime;
    time_t                       i_mtime;
    time_t                       i_ctime;
    unsigned long                i_blksize;
    unsigned long                i_blocks;
    unsigned long                i_version;
    unsigned long                i_nrpages;
    struct semaphore             i_sem;
    struct inode_operations      *i_op;
    struct super_block           *i_sb;
    struct wait_queue            *i_wait;
    struct file_lock             *i_flock;
    struct vm_area_struct        *i_mmap;
    struct page                  *i_pages;
    struct dquot                 *i_dquot[MAXQUOTAS];
    struct inode                 *i_next, *i_prev;
    struct inode                 *i_hash_next, *i_hash_prev;
    struct inode                 *i_bound_to, *i_bound_by;
    struct inode                 *i_mount;
    unsigned short               i_count;
    unsigned short               i_flags;
    unsigned char                i_lock;
    unsigned char                i_dirt;
    unsigned char                i_pipe;
    unsigned char                i_sock;
    unsigned char                i_seek;
    unsigned char                i_update;
    unsigned short               i_writecount;
    /* ways to hold type information in c, represented in union, and for ops polymorphism */
    union {
        struct pipe_inode_info   pipe_i;
        struct minix_inode_info  minix_i;
        struct ext_inode_info    ext_i;
        struct ext2_inode_info   ext2_i;
        struct hpfs_inode_info   hpfs_i;
        struct msdos_inode_info  msdos_i;
        struct umsdos_inode_info umsdos_i;
        struct iso_inode_info    isofs_i;
        struct nfs_inode_info    nfs_i;
        struct xiafs_inode_info  xiafs_i;
        struct sysv_inode_info   sysv_i;
        struct affs_inode_info   affs_i;
        struct ufs_inode_info    ufs_i;
        struct socket            socket_i;
        void                     *generic_ip;
    } u;
};
```
* ``` dev_t  i_rdev; ``` for inodes that represent device files, this field contains actural device number.
* ``` struct cdev *i_cdev;``` 
  * ```struct cdev``` kernel's internal structure that represents char devices
  * contains a pointer to ```struct cdev``` when the inode refers to a char device file
* obtain major minor number rather than directly accessing  i_rdev field, from inode
``` c
unsigned int iminor(struct inode *inode);
unsigned int imajor(struct inode *inode);
```

##Char Device Registration
* ```<linux/cdev.h>```, struct cdev
* runtime allocate and initializing
``` c
struct cdev *my_cdev = cdev_alloc();
/*my_cdev->ops = &my_fops;*/
cdev_init(my_cdev, my_fops);
my_cdev->owner = THIS_MODUL;
```
* registration ( to check the return value properly )
``` c
int cdev_add(struct cdev *dev, dev_t num, unsigned int count);
```
  * dev:
  * num: first device number to which this device responds
  * count: the number of device numbers that should be associated with the device (often 1)
  * __never add before all ops ready__
* remove
``` c
void cdev_del(struct cdev *dev);
```
  * __never called cdev after cdev_del__

##Device Registration in scull/ own device
* think of own device class derived from superclass ```struct cdev cdev```
* ```struct cdev cdev``` acted as 'base'
``` c
struct scull_dev {
	struct scull_qset *data; /* Pointer to first quantum set */
	int quantum; /* the current quantum size */
	int qset; /* the current array size */
	unsigned long size; /* amount of data stored here */
	unsigned int access_key; /* used by sculluid and scullpriv */
	struct semaphore sem; /* mutual exclusion semaphore */
	struct cdev cdev; /* Char device structure */
};
```
* override the cdev_init and instantiate own init/setup function/constructor
``` c
static void scull_setup_cdev(struct scull_dev *dev, int index)
{
	int err, devno = MKDEV(scull_major, scull_minor + index);
	cdev_init(&dev->cdev, &scull_fops);/* why init twice of scull_fops??!!! or this also allocates memeory*/
	dev->cdev.owner = THIS_MODULE;
	dev->cdev.ops = &scull_fops; /* ? */
	err = cdev_add (&dev->cdev, devno, 1);
	/* Fail gracefully if need be */
	if (err)
	printk(KERN_NOTICE "Error %d adding scull%d", err, index);
}
```
##open and release
###The open method
* tasks
	* check for device specifi errors
	* initialize the device if it is being opened for the __first time__
	* update the ```f_op``` pointer if necessray
	* allocate and fill the data structure to be put in ```filp->private_data```
* ```int (*open)(struct inode *inode, struct file *filp);```
  * tricks that assess the own cdev structure: or the derived scull_dev structure from inode
  ``` c
  #include <linux/kernel.h>
  container_of(pointer, container_type, container_field);
  ```
  * usage
  ``` c
  #include <linux/kernel.h>
  struct scull_dev *dev; /* device information */
  dev = container_of(inode->i_cdev, struct scull_dev, cdev);
  filp->private_data = dev; /* for other methods */
  ```

* ways to identify which device is being opened
  * first way: not clear what is the point to store private data
  * look at the minor number stored in the *__inode__* structure
    * must be used if device registered by __```register_chrdev```__
    * use __iminor__ to obtain
    * make sure it correspnds to a device that your driver is actually prepared to handle
###The release method
* tasks
  * Deallocate anything that open allocated in filp->private_data
  * Shut down the device on last close
* The close system call executes the release method only when the counter for the file structure drops to 0, which happens when the structure is destroyed. This relationship between the release method and the close system call guarantees that your driver sees only one release call for each open.
* flush method is called every time an application calls close(very few)

##before read and write: scull's memory usage
* memory allocation __policy(different from capacity)__ in scull
  * variable in length
    * write more to grow
    * trimming by overwritting the device with a shorter file
 
* two core functions to manage memory in kernel: kmalloc & kfree (not efficient or smart, just for demonstration)
``` c
#include <linux/slab.h>
void *kmalloc(size_t size, int flags);
void kfree(void *ptr);
```
##read and write
``` c
ssize_t read(struct file *filp, char _ _user *buff,
    size_t count, loff_t *offp);
ssize_t write(struct file *filp, const char _ _user *buff,
    size_t count, loff_t *offp);
```
* the buff argument to the read and write methods is a user-space pointer. cannot be directly dereferenced by kernel code.
  * reasons blablabla

* ways to asscess user-space buffer
``` c
#include <asm/uaccess.h>
unsigned long copy_to_user(void _ _user *to, 
                           const void *from, 
                           unsigned long count);
unsigned long copy_from_user(void *to, 
                             const void _ _user *from, 
                             unsigned long count);
```
  * above also used to check the __user from/to pointer validity
  
* Whatever the amount of data the methods transfer, they should generally update the file position at *offp to represent the current file position after successful completion of the system call. 
* error handling somewhat different from user-space, check return number carefully  


###The read method
* rules of return value
  * If the value equals the count argument passed to the read system call, the requested number of bytes has been transferred. This is the optimal case.

  * If the value is positive, but smaller than count, only part of the data has been transferred. This may happen for a number of reasons, depending on the device. Most often, the application program retries the read. For instance, if you read using the fread function, the library function reissues the system call until completion of the requested data transfer.

  * If the value is 0, end-of-file was reached (and no data was read).

  * A negative value means there was an error. The value specifies what the error was, according to <linux/errno.h>. Typical values returned on error include -EINTR (interrupted system call) or -EFAULT (bad address).
  * "should_block" in chapter 6

###The write method
* rules of return value
  * If the value equals count, the requested number of bytes has been transferred.

  * If the value is positive, but smaller than count, only part of the data has been transferred. The program will most likely retry writing the rest of the data.

  * If the value is 0, nothing was written. This result is not an error, and there is no reason to return an error code. Once again, the standard library retries the call to write. We'll examine the exact meaning of this case in Chapter 6, where blocking write is introduced.

  * A negative value means an error occurred; as for read, valid error values are those defined in <linux/errno.h>.
###readv and writev

  * partial transfer error? later
  

##Basic four methods as basic: open, realese, read, write
* try cp, dd, i/o redirection to test
* try free to see the mem
* printk
* __strace to monitor the system calls__

# Chapter 9 Communication with Hardware
##I/O Ports and I/O Memory
  
##Using I/O Ports
###I/O Port Allocation
``` c
#include <linux/ioport.h>
struct resource *request_region(unsigned long first, unsigned long n, 
                                const char *name);
```
* ensuring that you have exclusive access
* claim n ports, start with first, name should be name of your device
* return NULL on success
* allocated show up here /proc/ioports
