/*
 * This is a demo Linux kernel module.
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/ioport.h>

#define PORTA_BASE  0x40006000
#define PORTC_BASE  0x40006048
#define PORT_LENGTH (PORTA_BASE - PORTZ_BASE)

static int my_open(struct inode *inode, struct file *filp);
static int my_release(struct inode *inode, struct file *filp);
static ssize_t my_read( struct file *filp, 
                            char __user *buff,
                            size_t count, loff_t *offp);

static ssize_t my_write(struct file *filp,
                        const char __user *buff,
                        size_t count,
                        loff_t offp);

struct cdev my_cdev;
struct class *cl;
dev_t devno;

static struct file_operations myfops ={
    .owner = THIS_MODULE;
    .read = my_read;
    .write = my_write;
    .open = my_open;
    .release = my_release;
}


static int __init template_init(void)
{
	printk("Hello World, here is your module speaking hohhah\n");
	printk("this is the seeeeecond line!!\n");
	printk("and the third----\n");
	cdev_init(&my_cdev, &my_fops);
	cl = class_create(THIS_MODULE, "driver-gamepad");
	device_create(cl, NULL, devno, NULL, "driver-gamepad"); 
	return 0;
}


static void __exit template_cleanup(void)
{
	 printk("Short life for a small module...muha\n");
}

module_init(template_init);
module_exit(template_cleanup);

MODULE_DESCRIPTION("gamepad driver");
MODULE_LICENSE("GPL");

