#include "futosfs.h"
#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>

static struct stat getattr(char file_path){
    int file = open(file_path, O_RDONLY);

    struct stat file_info;


}

int main(){

};