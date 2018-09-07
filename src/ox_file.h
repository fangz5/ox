#include <stdio.h>

#ifndef _OX_FILE_H
#define _OX_FILE_H

typedef struct {
	FILE *fptr;
} ox__file_t;

int ox__file_create(ox__file_t *file, const char *pathname);

int ox__file_open(ox__file_t *file, const char *pathname);

int ox__file_close(const ox__file_t *file);

int ox__file_destroy(const char *pathname);

#endif
