#include <stdio.h>

#ifndef _OX_FILE_H
#define _OX_FILE_H

#define PAGE_SIZE 4096 * 2

typedef struct {
	FILE *fptr;
	int num_pages;
} ox__file_t;

int ox__file_create(ox__file_t *file, const char *pathname);

int ox__file_open(ox__file_t *file, const char *pathname);

int ox__file_close(const ox__file_t *file);

int ox__file_destroy(const char *pathname);

int ox__save_page(const ox__file_t *file, const void *page_content);

int ox__read_page(const ox__file_t *file, const int page_number, void *page_content);

#endif
