#Chapter 3
##The Design
* capabilities(mechanism)
* abstraction on top of memory
* types of devices and their interfaces & implementation
  * global and persistent
  * fifo: block and unblock, with /without interrupt
  * single,priv,uid,wuid(wait uid)

##Major and Minor Numbers
* /dev directory
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
