#include "ox_file.h"
#include <stdio.h>
#include <errno.h>
#include <unistd.h>


int ox__file_create(ox__file_t *file, const char *pathname)
{
	if (access(pathname, F_OK) == 0) {
		printf("Error Creating File: %s exists!\n", pathname);
		return -1;
	}

	FILE *file_ptr = fopen(pathname, "w");
	if (file_ptr == NULL) {
      	perror("Open File Error");
      	return -1;
	}
	file->fptr = file_ptr;
	return 0;
}

int ox__file_open(ox__file_t *file, const char *pathname, const char *mode)
{
	FILE *file_ptr = fopen(pathname, mode);
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
	if (access(pathname, F_OK) == 0) {
		if (remove(pathname) != 0) {
      		perror("Destroy File Error");
      		return -1;		
		}
	}
	return 0;
}

int ox__save_page(const ox__file_t *file, const void *page, const int page_number)
{
	fpos_t pos = PAGE_SIZE * page_number;
	if (fsetpos(file->fptr, &pos) != 0) {
		perror("File Position Error");
		return -1;
	}
	return ox__save_next_page(file, page);
}

int ox__save_next_page(const ox__file_t *file, const void *page)
{
	if (fwrite(page, PAGE_SIZE, 1, file->fptr) != 1) {
		perror("File Writing Error");
		return -1;
	}
	return 0;	
}

int ox__read_page(const ox__file_t *file, const int page_number, void *page)
{
	fpos_t pos = PAGE_SIZE * page_number;
	if (fsetpos(file->fptr, &pos) != 0) {
		perror("File Position Error");
		return -1;
	}
	return ox__read_next_page(file, page);
}

int ox__read_next_page(const ox__file_t *file, void *page)
{
	if (fread(page, PAGE_SIZE, 1, file->fptr) != 1) {
		perror("File Reading Error");
		return -1;
	}
	return 0;	
}
