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

int ox__save_page(const ox__file_t *file, const void *page_content)
{
	fpos_t pos = PAGE_SIZE * file->num_pages;
	if (fsetpos(file->fptr, &pos) != 0) {
		perror("File Position Error");
		return -1;
	}
	if (fwrite(page_content, PAGE_SIZE, 1, file->fptr) != 0) {
		perror("File Writing Error");
		return -1;
	}
	return 0;
}

int ox__read_page(const ox__file_t *file, const int page_number, void *page_content)
{
	if (page_number > file->num_pages) {
		printf("File Reading Error: Page number %d is greater total page number %d.\n", 
			page_number, file->num_pages);
		return -1;
	}		
	fpos_t pos = PAGE_SIZE * (page_number - 1);
	if (fsetpos(file->fptr, &pos) != 0) {
		perror("File Position Error");
		return -1;
	}
	if (fread(page_content, PAGE_SIZE, 1, file->fptr) != 0) {
		perror("File Reading Error");
		return -1;
	}
	return 0;
}
