/*
 * This is a demo Linux kernel module.
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/ioport.h>
#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/platform_device.h>

static int my_probe(struct platform_device *dev){
    printk("halla\n");
    return 0;
}
static int my_remove(struct platform_device *dev);

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
	platform_add_devices(1, 
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

