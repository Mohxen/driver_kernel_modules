#include <linux/module.h>
#include <linux/fs.h>         // For file_operations
#include <linux/cdev.h>       // For character device structure
#include <linux/uaccess.h>    // For copy_to_user function

#define DEVICE_NAME "char_device"
#define BUF_LEN 80

static int major;                 // Major number for the device
static char msg[BUF_LEN];         // Message buffer for the device
static struct cdev char_cdev;     // Character device structure

// Function prototypes for file operations
static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);
static ssize_t device_read(struct file *, char *, size_t, loff_t *);
static ssize_t device_write(struct file *, const char *, size_t, loff_t *);

// File operations structure
static struct file_operations fops = {
    .owner = THIS_MODULE,
    .read = device_read,
    .write = device_write,
    .open = device_open,
    .release = device_release
};

// Device open function
static int device_open(struct inode *inode, struct file *file) {
    printk(KERN_INFO "char_device: Device opened\n");
    return 0;
}

// Device release function
static int device_release(struct inode *inode, struct file *file) {
    printk(KERN_INFO "char_device: Device closed\n");
    return 0;
}

// Device read function
static ssize_t device_read(struct file *filp, char *buffer, size_t len, loff_t *offset) {
    int bytes_read = 0;
    char *msg_ptr = msg;  // Pointer to the message buffer

    // If *offset is greater than the length of msg, return 0 to indicate end of file
    if (*offset >= strlen(msg)) {
        return 0;
    }

    // Adjust msg_ptr based on the current offset
    msg_ptr += *offset;

    // Read data from msg to buffer, updating offset and len
    while (len && *msg_ptr) {
        put_user(*(msg_ptr++), buffer++);  // Copy data to user space
        len--;
        bytes_read++;
    }

    // Update the file offset to reflect how much data has been read
    *offset += bytes_read;

    printk(KERN_INFO "char_device: Read %d bytes\n", bytes_read);
    return bytes_read;
}


// Device write function
static ssize_t device_write(struct file *filp, const char *buffer, size_t len, loff_t *offset) {
    int i;
    for (i = 0; i < len && i < BUF_LEN - 1; i++) {
        get_user(msg[i], buffer + i);  // Get data from user space
    }
    msg[i] = '\0';  // Null terminate the string
    printk(KERN_INFO "char_device: Received %zu characters\n", len);
    return i;
}

// Module initialization function
static int __init char_device_init(void) {
    major = register_chrdev(0, DEVICE_NAME, &fops);
    if (major < 0) {
        printk(KERN_ALERT "char_device: Registering char device failed with %d\n", major);
        return major;
    }
    printk(KERN_INFO "char_device: Registered with major number %d\n", major);
    return 0;
}

// Module exit function
static void __exit char_device_exit(void) {
    unregister_chrdev(major, DEVICE_NAME);
    printk(KERN_INFO "char_device: Unregistered\n");
}

// Register module entry and exit points
module_init(char_device_init);
module_exit(char_device_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("A simple character device driver");
MODULE_AUTHOR("Your Name");
