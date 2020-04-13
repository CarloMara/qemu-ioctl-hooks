#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <mtd/mtd-user.h>
 
int main(int argc, char *argv[]){

    if(getuid() != 0){
        printf("Not run as root!\n");
        printf("This program will likely fail!\n\n");
    }

    printf("Trying to open %s\n", argv[1]);

    mtd_info_t mtd_info;

    int fd = open(argv[1], O_RDWR);

    if (fd == -1 & errno == EACCES){
        printf("Wrong permission for device\n");
        printf("Check filename or run as root\n");
        exit(-1);
    }

    int rc = ioctl(fd, MEMGETINFO, &mtd_info);
    if (rc == -1){
        printf("Something went wrong with the IOCTL.\n");
        exit(-1);
    }
    printf("MTD total size : %u bytes\n", mtd_info.size);
    printf("MTD erase size : %u bytes\n", mtd_info.erasesize);
 
    return 0;
}