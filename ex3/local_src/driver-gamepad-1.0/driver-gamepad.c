
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


#define GPIO_EXTIPSELL 0x100
#define GPIO_EXTIPSELH 0x104
#define GPIO_EXTIRISE  0x108
#define GPIO_EXTIFALL  0x10c
#define GPIO_IEN       0x110
#define GPIO_IFC       0x11c
#define GPIO_PC_MODEL  (0x04 + 0x48)
#define GPIO_PC_DOUT   (0x0c + 0x48)


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

dev_t devno;
struct cdev cdriver;
struct class *my_class;

struct file_operations my_fops = {
    .owner      = THIS_MODULE,
    .read       = my_read,
    .open       = my_open,
    .release    = my_release
};

static int my_probe(struct platform_device *dev){
    int err, irq_even, irq_odd;
    struct resource *res;
    struct resource *mem;
    
    printk(KERN_ERR "This is the probe!\n");
    
    
    err = alloc_chrdev_region(&devno, 0, 1, "driver-gamepad");
    if (err < 0){
        printk(KERN_ERR "Allocation failed");
    }
    printk(KERN_ERR "2!\n");
    res = platform_get_resource(dev, IORESOURCE_MEM, 0);
    if (!res){
        printk(KERN_ERR "Failed to get resource");
    }
    printk(KERN_ERR "3!\n");
    irq_even    = platform_get_irq(dev, 0);
    irq_odd     = platform_get_irq(dev, 1);
    
    my_class = class_create(THIS_MODULE, "driver-gamepad");
    device_create(my_class, NULL,devno, NULL, "driver-gamepad");
    
    printk(KERN_ERR "4!\n");
    mem = request_mem_region(res->start,res->end - res->start ,"tdt4258-mem");
    
    if(mem == 0){
        printk(KERN_ERR "Memory request failed");
    }
    printk(KERN_ERR "5!\n");
    
	iowrite32(  0x33333333  , res->start + (void*)GPIO_PC_MODEL);
    iowrite32(  0xff        , res->start + (void*)GPIO_PC_DOUT);
    iowrite32(  0x22222222  , res->start + (void*)GPIO_EXTIPSELL);
    iowrite32(  0xff        , res->start + (void*)GPIO_EXTIRISE);
    iowrite32(  0xff        , res->start + (void*)GPIO_EXTIFALL);
    iowrite32(  0xff        , res->start + (void*)GPIO_IEN);
    
    printk(KERN_ERR "6!\n");
    cdev_init(&cdriver, &my_fops);
    printk(KERN_ERR "7!\n");
    err = cdev_add(&cdriver, devno, 1);
    printk(KERN_ERR "8!\n");
    if (err < 0) {
        printk(KERN_ERR "Failed to activate char device.\n");
    }
    printk(KERN_ERR "probe finished\n");
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


