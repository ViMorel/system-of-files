#include "ressources/tosfs.h"
#include <sys/types.h>
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stddef.h>
#include <fcntl.h>
#include <sys/stat.h>

struct attributes{
    char name[64];
    size_t size;
    int block_number;
    
};


struct fuse_lowlevel_ops {
    struct stat (*getattr)(const char *file_path);
    int (*readdir)(void *map, struct attributes *list, int max_entries);
};
    


static struct stat getattr(char *file_path);
int readdir(void *map, struct attributes *list, int max_entries);