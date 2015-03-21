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
* major number: driver - device association
* minor number: referred the exact device

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

##Allocating and Freeing Device Numbers
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
  * *dev : an output-only parameter* that will, on successful completion, hold the first number in your allocated range
