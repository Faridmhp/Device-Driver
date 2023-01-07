/**************************************************************
 * Class:  CSC-415-01 Fall 2022
 * Name:Farid Mehdipour
 * Student ID:921571063
 * GitHub Name:Faridmhp
 * Project: Assignment 6 – Device-Driver
 *
 * File: <faridpass.c>
 *
 * Description:
 *   This file is the device driver called faridpass device driver.
 *  This device driver will encrypt the number that the user enters
 *  and then it will send the encrypted number to the user.
 *
 *
 **************************************************************/

#include <linux/init.h> 
#include <linux/module.h>  
#include <linux/fs.h>      // Header for the Linux file system support
#include <linux/uaccess.h> // Required for the copy to user function
#include <linux/cdev.h>    // Header for the character device structure
#include <linux/device.h>  // Header to support the kernel Driver Model
#include <linux/kernel.h>  // functions for the kernel including macros, types
#include <linux/errno.h>   // Error codes
#include <linux/types.h>   // Type definitions
#include <linux/kdev_t.h>  // MAJOR, MINOR macros
#include <linux/slab.h>    // kmalloc()
#include <linux/ioctl.h>   // ioctl macros


#define DEVICE_NAME "faridpass" // The device will appear at /dev/encrypt using this value
#define CLASS_NAME "faridpassClass"  // The device class
#define STR_LEN 8                 // Length of the string

// struct cdev passCdev; // The character device structure
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Farid Mehdipour");
MODULE_DESCRIPTION("A simple Linux int driver for encrypting numbers");

static int majorNumber;

static struct class *passCdev = NULL; // The device-driver class
static struct device *passdev = NULL; // The device-driver device

static int devOpen(struct inode *, struct file *);
static int devRelease(struct inode *, struct file *);
static ssize_t devRead(struct file *, char *, size_t, loff_t *);
static ssize_t devWrite(struct file *, const char *, size_t, loff_t *);
static long devIoctl(struct file *, unsigned int, unsigned long);


typedef struct passStructure
{
    int numbers;
    int passNum;
    char *passStr;

} passStructure;


static struct passStructure *ddStruct = 0; // The device-driver structure



struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = devOpen,
    .release = devRelease,
    .read = devRead,
    .write = devWrite,
    .unlocked_ioctl = devIoctl,
};

static int __init encrypt_init(void)
{
    int ddResult;
    dev_t dev;

    ddStruct = vmalloc(sizeof(struct passStructure));

    if (ddStruct == 0)
    {
        printk(KERN_INFO "ddStruct vmalloc error"); // TODO
        return -1;
    }

    ddStruct->passNum = 0;
    ddStruct->numbers = 0;
    ddStruct->passStr = vmalloc(STR_LEN);


    // Register the device
    majorNumber = register_chrdev(0, DEVICE_NAME, &fops);
    if (majorNumber < 0)
    {
        printk(KERN_ALERT "Failed to register a major number \n");
        return majorNumber;
    }

    printk(KERN_INFO "Registered correctly with major number %d \n", majorNumber);


    //register the device class
    passCdev = class_create(THIS_MODULE, CLASS_NAME);
    if (IS_ERR(passCdev))
    {
        unregister_chrdev(majorNumber, DEVICE_NAME);
        printk(KERN_ALERT "Failed to create the device class \n");
        return PTR_ERR(passCdev);
    }

    printk(KERN_INFO "Device class registered\n");

    //register the device driver
    passdev = device_create(passCdev, NULL, MKDEV(majorNumber, 0), NULL, DEVICE_NAME);
    if (IS_ERR(passdev))
    {
        class_destroy(passCdev);
        unregister_chrdev(majorNumber, DEVICE_NAME);
        printk(KERN_ALERT "Failed to create the device \n");
        return PTR_ERR(passdev);
    }

    printk(KERN_INFO "Device class created\n");


    return 0;
}

static void __exit encrypt_exit(void)
{

    printk(KERN_INFO "encrypt: Exiting the encrypt\n");

    // // Free the memory for the ddStruct structure
    vfree(ddStruct->passStr);
    vfree(ddStruct);
    vfree(ddStruct->passStr);

    // Unregister the device
    device_destroy(passCdev, MKDEV(majorNumber, 0));
    class_unregister(passCdev);
    class_destroy(passCdev);
    unregister_chrdev(majorNumber, DEVICE_NAME);

}

static int devOpen(struct inode *inodep, struct file *filep)
{
    filep->private_data = ddStruct; // TODO
    printk(KERN_INFO "Device has been opened \n");
    return 0;
}

static ssize_t devRead(struct file *filep, char *buffer, size_t len, loff_t *offset)
{
    char *pointer;   // TODO
    ddStruct = (struct passStructure *)filep->private_data;
    printk(KERN_INFO "passNum: %d", ddStruct->passNum); // TODO

    pointer = ddStruct->passStr;

    if (ddStruct->numbers == 0) // TODO
    {
        printk(KERN_INFO "No data to read \n");
        return 0;
    }

    copy_to_user(buffer, pointer, strlen(ddStruct->passStr));
    printk(KERN_INFO "Sent %d characters to the user \n", STR_LEN);


    return 0;
}



static ssize_t devWrite(struct file *filep, const char *buffer, size_t len, loff_t *offset)
{

    int *num;    // TODO
    num = vmalloc(sizeof(int));
    copy_from_user(num, buffer, sizeof(int));

    ddStruct = (struct passStructure *)filep->private_data;

    ddStruct->numbers = ddStruct->numbers + 1; // TODO

    switch (*num)
    {
    case 0:
        ddStruct->passNum = 0;
        ddStruct->passStr = "~";
        break;
    case 1:
        ddStruct->passNum = 1;
        ddStruct->passStr = "!";
        break;
    case 2:
        ddStruct->passNum = 2;
        ddStruct->passStr = "@";
        break;
    case 3:
        ddStruct->passNum = 3;
        ddStruct->passStr = "#";
        break;
    case 4:
        ddStruct->passNum = 4;
        ddStruct->passStr = "$";
        break;
    case 5:
        ddStruct->passNum = 5;
        ddStruct->passStr = "%";
        break;
    case 6:
        ddStruct->passNum = 6;
        ddStruct->passStr = "^";
        break;
    case 7:
        ddStruct->passNum = 7;
        ddStruct->passStr = "&";
        break;
    case 8:
        ddStruct->passNum = 8;
        ddStruct->passStr = "*";
        break;
    case 9:
        ddStruct->passNum = 9;
        ddStruct->passStr = "(";
        break;
    default:
        ddStruct->passStr = "?";
        break;
    }

    printk(KERN_INFO "Password number is %d \n", ddStruct->passNum);

    return ddStruct->passStr;
}





static long devIoctl(struct file *filep, unsigned int cmd, unsigned long arg)
{
    if (cmd != 3)
    {
        printk(KERN_ERR "Error devIoctl\n");
        return -1;
    }

    return 0;
}


static int devRelease(struct inode *inodep, struct file *filep)
{
    ddStruct = (struct passStructure *)filep->private_data;
    printk(KERN_INFO "encrypt: Device successfully closed \n");
    return 0;
}


module_init(encrypt_init);
module_exit(encrypt_exit);
