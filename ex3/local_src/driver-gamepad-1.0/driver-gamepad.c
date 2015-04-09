
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
#include <linux/signal.h>


#define GPIO_EXTIPSELL 0x100
#define GPIO_EXTIPSELH 0x104
#define GPIO_EXTIRISE  0x108
#define GPIO_EXTIFALL  0x10c
#define GPIO_IEN       0x110
#define GPIO_IFC       0x11c
#define GPIO_PC_DIN    (0x1c + 0x48)
#define GPIO_PC_MODEL  (0x04 + 0x48)
#define GPIO_PC_DOUT   (0x0c + 0x48)

/*
    struct containing information of the driver
    initialized during probe and init functions
*/
struct gamepad{
    int active;
    dev_t devno;
    struct cdev cdriver;
    struct class *my_class;
    struct resource *res;
    struct resource *mem;
    int irq_odd, irq_even;
    struct fasync_struct *async_queue; 
};

struct gamepad gamepad_driver;

irqreturn_t interrupt_handler(int irq, void *dev_id, struct pt_regs *regs){
    iowrite32(0xff, gamepad_driver.res->start + (void*)GPIO_IFC);
    printk(KERN_ERR "int handler\n");
    //if(&gamepad_driver.async_queue){
    kill_fasync(&(gamepad_driver.async_queue), SIGIO, POLL_IN);
    //}
    return IRQ_HANDLED;
}


/*
    free IRQ lines if the driver is closed by the last process
*/

int my_release(struct inode *inode, struct file *filp){
    printk(KERN_ERR "release\n");
    
    *gamepad_driver.active -= 1;
    
    if (gamepad_driver.active == 0){
        free_irq(   gamepad_driver.irq_odd , &gamepad_driver.cdriver );
        free_irq(   gamepad_driver.irq_even, &gamepad_driver.cdriver );
    }
    
    return 0;
}

/*
    request IRQ lines if the driver is opened by the first process
*/
int my_open(struct inode *inode, struct file *filp){
    printk(KERN_ERR "open\n");
    
    if(gamepad_driver.active == 0){
        request_irq(    gamepad_driver.irq_even,
                        interrupt_handler,
                        0,
                        "driver-gamepad",
                        &gamepad_driver.cdriver);
        
        request_irq(    gamepad_driver.irq_odd,
                        interrupt_handler,
                        0,
                        "driver-gamepad",
                        &gamepad_driver.cdriver);
    }
    
    gamepad_driver.active += 1;
    return 0;
}

ssize_t my_read(struct file *filp, char __user *buff, size_t count, loff_t *offp){
    int data = ~ioread32(gamepad_driver.res->start + (void*)GPIO_PC_DIN);
    copy_to_user(buff, &data, 1);
    return 0;
}

static int my_fasync(int fd, struct file *filp, int mode){
    return fasync_helper(fd, filp, mode, &(gamepad_driver.async_queue));
}

struct file_operations my_fops = {
    .owner      = THIS_MODULE,
    .read       = my_read,
    .open       = my_open,
    .release    = my_release,
    .fasync     = my_fasync,
};

static int my_probe(struct platform_device *dev){
    int err;
    gamepad_driver.active = 0;
    
    printk(KERN_ERR "This is the probe!\n");
    
    err = alloc_chrdev_region(&gamepad_driver.devno, 0, 1, "driver-gamepad");
    if (err < 0){
        printk(KERN_ERR "Allocation failed");
    }
    gamepad_driver.res = platform_get_resource(dev, IORESOURCE_MEM, 0);
    if (!gamepad_driver.res){
        printk(KERN_ERR "Failed to get resource");
    }
    
    gamepad_driver.my_class = class_create(THIS_MODULE, "driver-gamepad");
    device_create(gamepad_driver.my_class,
                    NULL,
                    gamepad_driver.devno,
                    NULL,
                    "driver-gamepad");
    
    gamepad_driver.mem = request_mem_region(
                        gamepad_driver.res->start,
                        gamepad_driver.res->end - gamepad_driver.res->start,
                        "tdt4258-mem");
    
    if(gamepad_driver.mem == 0){
        printk(KERN_ERR "Memory request failed");
    }
    
    
	iowrite32( 0x33333333 , gamepad_driver.res->start + (void*)GPIO_PC_MODEL);
    iowrite32( 0xff       , gamepad_driver.res->start + (void*)GPIO_PC_DOUT);
    iowrite32( 0x22222222 , gamepad_driver.res->start + (void*)GPIO_EXTIPSELL);
    iowrite32( 0xff       , gamepad_driver.res->start + (void*)GPIO_EXTIRISE);
    iowrite32( 0xff       , gamepad_driver.res->start + (void*)GPIO_EXTIFALL);
    iowrite32( 0xff       , gamepad_driver.res->start + (void*)GPIO_IEN);
    
    gamepad_driver.irq_even    = platform_get_irq(dev, 0);
    gamepad_driver.irq_odd     = platform_get_irq(dev, 1);
    
    cdev_init(&gamepad_driver.cdriver, &my_fops);
    
    err = cdev_add(&gamepad_driver.cdriver, gamepad_driver.devno, 1);
    if (err < 0) {
        printk(KERN_ERR "Failed to activate char driver.\n");
    }
    printk(KERN_ERR "probe finished\n");
    return 0;
}


static int my_remove(struct platform_device *dev){
    printk(KERN_ERR "remove");
    return 0;
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


