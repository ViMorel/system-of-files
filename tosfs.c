#include "ressources/tosfs.h"
#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>


int main(){
    int file = open("ressources/test_tosfs_files", O_RDONLY);

    struct stat file_info;
    fstat(file, &file_info);
    
    printf("st_size is : %ld \r\n", file_info.st_size);
    void* map;
    map = mmap(NULL,file_info.st_size, PROT_READ, MAP_PRIVATE, file, 0);

    struct tosfs_superblock *superblock = (struct tosfs_superblock *)map;

    struct tosfs_inode *inode = (struct tosfs_inode *)((char*) map + TOSFS_BLOCK_SIZE);

    struct tosfs_dentry *dentry = (struct tosfs_dentry *)((char*) map + 2*TOSFS_BLOCK_SIZE);

    printf("superblock.inodes : %u \r\n", superblock->inodes);

    printf("superblock.blocks : %u \r\n", superblock->blocks);

    printf("superblock.block_size : %u \r\n", superblock->block_size);

    printf("inode.size : %u \r\n", inode->size);

    printf("dentry.name : %s \r\n", dentry->name);

    munmap(map, file_info.st_size);
};