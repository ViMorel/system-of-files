/*
static struct fuse_lowlevel_ops hello_ll_oper = {
	.lookup		= hello_ll_lookup,
	.getattr	= hello_ll_getattr,
	.readdir	= hello_ll_readdir,
	.open		= hello_ll_open,
	.read		= hello_ll_read,
};

*/

#include "struct_fuse.h"
#include "tosfs.h"
#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>


int file = open("ressources/test_tosfs_files", O_RDONLY);

void getattr(){

}



static struct fuse_lowlevel={
    .getattr=getattr;
    .
}