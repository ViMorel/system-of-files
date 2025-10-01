#include "ressources/tosfs.h"
#include <sys/types.h>
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stddef.h>
#include <fcntl.h>
#include <sys/stat.h>

struct attributes{
    char* name;
    size_t size;
    __u32 blocks;
    __u32 block_size;
    __u32 inode;
    __u16 file_type;
    __u16 perms;
    __u16 user_id;
    char* dentry_name;
};

struct fuse_lowlevel_ops {
    struct stat (*getattr)(const char *file_path);
    int (*readdir)(void *map, struct attributes *list, int max_entries);
};
    

void getattr(char *file_path);

int readdir(void *map, struct attributes *list, int max_entries);