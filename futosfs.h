#include "ressources/tosfs.h"

struct attributes{
    char name;
    size_t size;
    int block_number;
    
};

static struct stat getattr(char file_path);
static void readdir();