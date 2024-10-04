#include <linux/module.h>  // Needed for all kernel modules
#include <linux/kernel.h>  // Needed for KERN_INFO
#include <linux/init.h>    // Needed for the macros

// This function is called when the module is loaded
static int __init hello_init(void) {
    printk(KERN_INFO "Hello, World!\n");
    return 0; // Return 0 for success
}

// This function is called when the module is removed
static void __exit hello_exit(void) {
    printk(KERN_INFO "Goodbye, World!\n");
}

// Macros to register module entry and exit points
module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("A simple Hello World kernel module");
