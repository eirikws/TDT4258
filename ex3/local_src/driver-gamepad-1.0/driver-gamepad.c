/*
 * This is a demo Linux kernel module.
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <asm/uaccess.h>
#include <asm/io.h>
#include <linux/platform_device.h>
#include <linux/device.h>
#include <linux/interrupt.h>
#include <linux/ioport.h>
#include <linux/mm.h>
#include "efm32gg.h"

irqreturn_t interrupt_handler(int irq, void *dev_id, struct pt_regs *regs){
    printk("int handler\n");
}

int my_release(struct inode *inode, struct file *filp) {
    printk("release\n");
    return 0;
}

int my_open(struct inode *inode, struct file *filp) {
    printk("open\n");
    return 0;
}


ssize_t my_read(struct file *filp, char __user *buff, size_t count, loff_t *offp){
    printk("read\n");
    return 0;
}

dev_t my_device;
struct cdev *cdriver;
struct class *my_class;

struct file_operations my_fops = {
    .owner      = THIS_MODULE,
    .read       = my_read,
    .open       = my_open,
    .release    = my_release
};

static int my_probe(struct platform_device *dev){
    printk("This is the probe!\n");
    
    int err = alloc_chrdev_region(&my_device, 0, 1, "driver-gamepad");
    if (err < 0){
        printk(KERN_ERR "Allocation failed");
    }
    
    my_class = class_create(THIS_MODULE, "driver-gamepad");
    device_create(my_class, NULL,1, NULL, "driver-gamepad");
    
    struct resource *gpio_portC_mem = request_mem_region(GPIO_PC_BASE,0x24,"gpio_port_c");
    
    if(gpio_portC_mem == 0){
        printk(KERN_ERR "Memory request gpio port C failed");
    }
    
    struct resource *gpio_gen_mem = request_mem_region(GPIO_GEN_BASE,GPIO_GEN_SIZE,"gpio_gen");
    
    if(gpio_gen_mem == 0){
        printk(KERN_ERR "Memory request gpio general failed");
    }
    
	iowrite32(0x33333333, GPIO_PC_MODEL);
    iowrite32(0xff, GPIO_PC_DOUT);
    iowrite32(0x22222222, GPIO_EXTIPSELL);
    iowrite32(0xff, GPIO_EXTIRISE);
    iowrite32(0xff, GPIO_EXTIFALL);
    iowrite32(0xff, GPIO_IEN);
    
    cdriver = cdev_alloc();
    cdriver->owner = THIS_MODULE;
    cdriver->ops = &my_fops;
    
    err = cdev_add(cdriver, my_device, 1);
    if (err < 0) {
        printk(KERN_ERR "Failed to activate char device.\n");
    }
    
    return 0;
}
static int my_remove(struct platform_device *dev){
    printk(KERN_ERR "remove");
}

static const struct of_device_id my_of_match[]={
    {   .compatible = "tdt4258", },
    {   },
};

static struct platform_driver my_driver ={
    .probe = my_probe,
    .remove = my_remove,
    .driver = {
        .name   = "my",
        .owner  = THIS_MODULE,
        .of_match_table = my_of_match,
    },
};

//static struct platform_device{
    

static int __init template_init(void)
{
	printk("Hello World, here is your module speaking hohhah\n");
    platform_driver_register(&my_driver);
	printk("after\n");
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


