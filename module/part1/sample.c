#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Bryan Tsai");
MODULE_DESCRIPTION("A simple example Linux module.");
MODULE_VERSION("0.01");


static int __init example_init(void) {
  printk(KERN_INFO "Module installed.\n");
  return 0;
}

static void __exit example_exit(void) {
  printk(KERN_INFO "Module removed.\n");
}


module_init(example_init)
module_exit(example_exit)



