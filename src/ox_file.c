#include "ox_file.h"
#include <stdio.h>
#include <errno.h>


int ox__file_create(ox__file_t *file, const char *pathname)
{
	FILE *file_ptr = fopen(pathname, "w");
	if (file_ptr == NULL) {
      	perror("Open File Error");
      	return -1;
	}
	file->fptr = file_ptr;
	return 0;
}

int ox__file_open(ox__file_t *file, const char *pathname)
{
	FILE *file_ptr = fopen(pathname, "r");
	if (file_ptr == NULL) {
      	perror("Open File Error");
      	return -1;
	}
	file->fptr = file_ptr;
	return 0;
}

int ox__file_close(const ox__file_t *file)
{
	if (fclose(file->fptr) != 0) {
      	perror("Close File Error");
      	return -1;		
	}
	return 0;
}

int ox__file_destroy(const char *pathname)
{
	if (remove(pathname) != 0) {
      	perror("Destroy File Error");
      	return -1;		
	}
	return 0;
}
