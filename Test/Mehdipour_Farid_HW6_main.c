/**************************************************************
* Class:  CSC-415-01 Fall 2022
* Name:Farid Mehdipour
* Student ID:921571063
* GitHub Name:Faridmhp
* Project: Assignment 6 – Device-Driver
*
* File: <Mehdipour_Farid_HW6_main.c>
*
* Description:
    This test file is used to test the device driver called faridpass.
    This test file will ask the user to enter a number and then it will
    send that number to the device driver and then it will read the number
    and write the encrypted number from the device driver and print it out.
*
**************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>

#define DEVICE_NAME "faridpass"
#define STR_LEN 8



int main(int argc, char *argv[])
{

    int fd = 0;
    int ret = 0;
    int numbers = 0;
    int passNum = 0;
    char *passStr = (char *)malloc(STR_LEN);

    fd = open("/dev/faridpass", O_RDWR);

    if (fd < 0)
    {
        printf("Error opening file");
        return -1;
    }

    printf("Enter the password number: ");
    scanf("%d", &numbers);

    ret = write(fd, &numbers, sizeof(numbers));

    if (ret < 0)
    {
        printf("Error writing to file. \n");
        return -1;
    }

    ret = read(fd, &numbers, sizeof(numbers));

    if (ret < 0)
    {
        printf("Error reading from file. \n");
        return -1;
    }

    printf("The number is: %d \n", numbers);

    return 0;    
}

