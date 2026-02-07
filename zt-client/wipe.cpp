#include "include/wipe.hpp"
#include "include/dev.hpp"
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <linux/fs.h>
#include <cstring>
#include <iostream>
#include <vector>


#define MP_NUM_PASSES 3

bool mpOverwrite(const std::string& devicePath){
    int fd = open(devicePath.c_str(), O_WRONLY | O_SYNC);
    if (fd < 0) {
        perror("open");
        return false;
    }

    uint64_t size = 0;
    if (ioctl(fd, BLKGETSIZE64, &size) < 0) {
        perror("BLKGETSIZE64");
        close(fd);
        return false;
    }

    constexpr size_t BLKSIZE = 1024 * 1024; // 1 MiB
    std::vector<char> zeroBuf(BLKSIZE, 0);


    for (int pass = 0; pass < MP_NUM_PASSES; pass++) {
        if (lseek(fd, 0, SEEK_SET) < 0) {
            perror("lseek");
            close(fd);
            return false;
        }

        uint64_t written = 0;
        while (written < size) {
            size_t toWrite = std::min<uint64_t>(BLKSIZE, size - written);
            ssize_t w = write(fd, zeroBuf.data(), toWrite);

            if (w < 0) {
                perror("write");
                close(fd);
                return false;
            }
            written += w;
        }

        if (fsync(fd) < 0) {
            perror("fsync");
            close(fd);
            return false;
        }
    }

    close(fd);
    return true;
    
    return true;
}

bool wipeDisk(const std::string& devicePath, WipeMethod
        method){

    switch(method){
        case WipeMethod::ATA_SECURE_ERASE:
            break;
        case WipeMethod::FIRMWARE_ERASE:
            break;
        case WipeMethod::PLAIN_OVERWRITE:
            return mpOverwrite(devicePath);
        case WipeMethod::ENCRYPTED_OVERWRITE:
            break;
        default:
            std::cout << "Unsupported Wipe Method\n";

    }

}
