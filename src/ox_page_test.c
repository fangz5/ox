#include "../src/ox_file.h"
#include "minunit.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int tests_run = 0;
char test_dataset[] = "test_dataset";
ox__file_t file_handle;

static char *test_page_write() {
	mu_assert("ERROR(file_create): unable to create file.", 
		0 == ox__file_create(&file_handle, test_dataset));

	char *page_content = malloc(PAGE_SIZE);
	int size_of_int = sizeof(int);
	const int M = PAGE_SIZE / size_of_int;
	for (int i = 0; i < M; i++) {
		*(int *)(page_content + i * size_of_int) = i;
	}

	mu_assert("ERROR(page_write): unable to save page.",
		0 == ox__save_page(&file_handle, page_content));

	mu_assert("ERROR(file_close): unable to create file.", 
		0 == ox__file_close(&file_handle));

	free(page_content);
	return 0;
}

static char *test_page_read() {
	mu_assert("ERROR(file_open): unable to open file.", 
		0 == ox__file_open(&file_handle, test_dataset));

	char *page_content = malloc(PAGE_SIZE);
	int size_of_int = sizeof(int);
	const int M = PAGE_SIZE / size_of_int;

	mu_assert("ERROR(page_read): unable to read page.", 
		0 == ox__read_page(&file_handle, 1, page_content));

	int x;
	for (int i = 0; i < M; i++) {
		memcpy((void *)&x, page_content + i * size_of_int, size_of_int);
		mu_assert("ERROR(page_read): readback value does not equal written value.",
			x == i);
	}

	mu_assert("ERROR(file_close): unable to create file.", 
		0 == ox__file_close(&file_handle));

	free(page_content);
	return 0;
}


static char *all_tests() {
  mu_run_test(test_page_write);
  mu_run_test(test_page_read);
  return 0;
}

int main(void) {
	ox__file_destroy(test_dataset);

  	char *result = all_tests();
  	if (result != 0) {
    	printf("%s\n", result);
  	}
  	else {
    	printf("ALL TESTS in page_test PASSED\n");
  	}

  	return 0;
}

