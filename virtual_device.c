#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/cdev.h>

#define DEVICE_NAME "virtual_device"
#define CLASS_NAME "virtual"

static dev_t dev_num;
static struct class *device_class;
static struct cdev virtual_cdev;

static char device_buffer[256] = {0};

static long process_isa(int op_code, long a, long b) {
    switch (op_code) {
        case 0x01: // ADD
            return a + b;
        case 0x02: // MULTIPLY
            return a * b;
        case 0x03: // POWER
            {
                long result = 1;
                for (long i = 0; i < b; i++) {
                    result *= a;
                }
                return result;
            }
        default:
            printk(KERN_ERR "Virtual Device: Invalid OP_CODE %d\n", op_code);
            return -EINVAL;
    }
}

static ssize_t device_write(struct file *file, const char __user *user_buffer, size_t len, loff_t *offset) {
    char input_buffer[256] = {0};
    int op_code;
    long a, b, result;

    if (len > 255) {
        len = 255;
    }
    if (copy_from_user(input_buffer, user_buffer, len)) {
        return -EFAULT;
    }

    if (sscanf(input_buffer, "%d %ld %ld", &op_code, &a, &b) != 3) {
        printk(KERN_ERR "Virtual Device: Invalid ISA command\n");
        return -EINVAL;
    }

    result = process_isa(op_code, a, b);
    snprintf(device_buffer, sizeof(device_buffer), "%ld", result);
    printk(KERN_INFO "Virtual Device: Processed OP_CODE %d with args (%ld, %ld) = %ld\n", op_code, a, b, result);

    return len;
}

static ssize_t device_read(struct file *file, char __user *user_buffer, size_t len, loff_t *offset) {
    size_t data_len = strlen(device_buffer);
    if (*offset >= data_len) {
        return 0;
    }
    if (len > data_len - *offset) {
        len = data_len - *offset;
    }
    if (copy_to_user(user_buffer, device_buffer + *offset, len)) {
        return -EFAULT;
    }
    *offset += len;
    return len;
}

static struct file_operations fops = {
    .read = device_read,
    .write = device_write,
};

static int __init virtual_device_init(void) {
    if (alloc_chrdev_region(&dev_num, 0, 1, DEVICE_NAME) < 0) {
        return -1;
    }

    device_class = class_create(CLASS_NAME);
    if (IS_ERR(device_class)) {
        unregister_chrdev_region(dev_num, 1);
        return PTR_ERR(device_class);
    }

    if (device_create(device_class, NULL, dev_num, NULL, DEVICE_NAME) == NULL) {
        class_destroy(device_class);
        unregister_chrdev_region(dev_num, 1);
        return -1;
    }

    cdev_init(&virtual_cdev, &fops);
    if (cdev_add(&virtual_cdev, dev_num, 1) == -1) {
        device_destroy(device_class, dev_num);
        class_destroy(device_class);
        unregister_chrdev_region(dev_num, 1);
        return -1;
    }

    printk(KERN_INFO "Virtual Device: Module loaded\n");
    return 0;
}

static void __exit virtual_device_exit(void) {
    cdev_del(&virtual_cdev);
    device_destroy(device_class, dev_num);
    class_destroy(device_class);
    unregister_chrdev_region(dev_num, 1);
    printk(KERN_INFO "Virtual Device: Module unloaded\n");
}

module_init(virtual_device_init);
module_exit(virtual_device_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ChatGPT");
MODULE_DESCRIPTION("Virtual device with ISA processing");
MODULE_VERSION("1.0");
