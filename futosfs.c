#include "futosfs.h"

#include <string.h>

static struct stat getattr(char *file_path){
    struct stat file_info;
    stat(file_path, &file_info);
    return file_info;
}

int readdir(void *map, struct attributes *list, int max_entries) {
    struct tosfs_superblock *superblock = (struct tosfs_superblock *)map;
    struct tosfs_inode *inode = (struct tosfs_inode *)((char*)map + TOSFS_INODE_BLOCK * TOSFS_BLOCK_SIZE);
    struct tosfs_dentry *dentry = (struct tosfs_dentry *)((char*)map + TOSFS_ROOT_BLOCK * TOSFS_BLOCK_SIZE);

    int count = 0;
    for(int i = 0; i < superblock->inodes && count < max_entries; i++) {
        if (inode[i].inode == 0) continue;
        strncpy(list[count].name, dentry[i].name, 63);
        list[count].name[63] = 0;
        list[count].size = inode[i].size;
        list[count].block_number = inode[i].block_no;
        count++;
    }
    return count;
}

struct fuse_lowlevel_ops futosfs_ops = {
    .getattr = getattr,
    .readdir = readdir
};

int main(){

    // -----------------------Test the getattr function------------------------
    
    /*
    struct stat info = getattr("ressources/test_tosfs_files");
    printf("File size: %ld bytes\n", info.st_size);
    printf("Number of links: %ld\n", info.st_nlink);
    printf("File inode: %ld\n", info.st_ino);
    printf("File permissions: %o\n", info.st_mode & 0777);
    return 0;
    */
    
    // -----------------------Test the readdir function------------------------

    /*
    int file = open("ressources/test_tosfs_files", O_RDONLY);

    struct stat file_info;
    fstat(file, &file_info);
    
    printf("st_size is : %ld \r\n", file_info.st_size);
    void* map;
    map = mmap(NULL,file_info.st_size, PROT_READ, MAP_PRIVATE, file, 0);

    struct attributes list[32];
    int entries = readdir(map, list, 32);
    printf("Number of entries: %d\n", entries);
    for(int i = 0; i < entries; i++) {
        printf("Name: %s, Size: %zu, Block Number: %d\n", list[i].name, list[i].size, list[i].block_number);
    }

    munmap(map, file_info.st_size);
    return 0;
    */
};