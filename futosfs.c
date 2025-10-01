#include "futosfs.h"
#include <stdio.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <string.h>

void print_mode(__u16 mode, __u16 perms) {
    char typechar = (mode == IF_DIR) ? 'd' : '-';
    char permchar = (perms == 0) ? 'x' : ((perms == 1) ? 'r' : 'w');

    printf("perms are : %c\n", permchar);
    printf("mode is : %c\n", typechar);
}

void getattr(char *file_path){
    int file_id = open(file_path, O_RDONLY);
    struct attributes file_attributes;

    off_t lenght = lseek(file_id, 0, SEEK_END);
    void* map = mmap(NULL, lenght, PROT_READ, MAP_PRIVATE, file_id, 0);
    struct tosfs_superblock *superblock = (struct tosfs_superblock *)map;
    struct tosfs_inode *inode           = (struct tosfs_inode *)((char*)map + TOSFS_INODE_BLOCK * TOSFS_BLOCK_SIZE);
    struct tosfs_dentry *dentry         = (struct tosfs_dentry *)((char*)map + TOSFS_ROOT_BLOCK * TOSFS_BLOCK_SIZE);

    file_attributes.name          = file_path;
    file_attributes.size          = lenght;
    file_attributes.blocks        = superblock->blocks;
    file_attributes.block_size    = superblock->block_size;
    file_attributes.inode         = inode->inode;
    file_attributes.file_type     = inode->mode;
    file_attributes.perms         = inode->perm;
    file_attributes.user_id       = inode->uid;
    file_attributes.dentry_name   = ((char *)dentry->name);
    printf("name          = %s\n", file_attributes.name);
    printf("size          = %zu\n", file_attributes.size);
    printf("blocks        = %u\n", file_attributes.blocks);
    printf("block_size    = %u\n", file_attributes.block_size);
    printf("inode         = %u\n", file_attributes.inode);
    print_mode(file_attributes.file_type, file_attributes.perms);
    printf("user_id       = %hu\n", file_attributes.user_id);
    printf("dentrys_inode = %s\n", file_attributes.dentry_name);
    
    munmap(map, lenght);
};

/*int readdir(void *map, struct attributes *list, int max_entries) {
    struct tosfs_superblock *superblock = (struct tosfs_superblock *)map;
    struct tosfs_inode *inode           = (struct tosfs_inode *)((char*)map + TOSFS_INODE_BLOCK * TOSFS_BLOCK_SIZE);
    struct tosfs_dentry *dentry         = (struct tosfs_dentry *)((char*)map + TOSFS_ROOT_BLOCK * TOSFS_BLOCK_SIZE);

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
};*/

void readdir(char *file_path) {
    int file_id = open(file_path, O_RDONLY);
    if (file_id < 0) { perror("open"); return; }

    off_t lenght = lseek(file_id, 0, SEEK_END);
    if (lenght <= 0) { perror("lseek"); close(file_id); return; }
    printf("lenght is: %ld\n\r", lenght);
    void* map = mmap(NULL, lenght, PROT_READ, MAP_PRIVATE, file_id, 0);
    if (map == MAP_FAILED) { perror("mmap"); close(file_id); return; }
    struct tosfs_superblock *superblock = (struct tosfs_superblock *)map;
    struct tosfs_inode *inode           = (struct tosfs_inode *)((char*)map + TOSFS_INODE_BLOCK * TOSFS_BLOCK_SIZE);
    struct tosfs_dentry *dentry         = (struct tosfs_dentry *)((char*)map + TOSFS_ROOT_BLOCK * TOSFS_BLOCK_SIZE);


    struct passwd *pw = getpwuid(inode->uid);
    struct group  *gr = getgrgid(inode->gid);

    printf("%d %2u %s %s %6u %s\n",
        inode->perm,
        inode->nlink,
        pw ? pw->pw_name : "?",
        gr ? gr->gr_name : "?",
        inode->size,
        dentry->name
    );
    munmap(map, lenght);
};

/*struct fuse_lowlevel_ops futosfs_ops = {
    .getattr = getattr,
    .readdir = readdir
};*/

int main(){
    getattr("ressources/test_tosfs_files");
    readdir("ressources");
    
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