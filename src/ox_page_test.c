#include "../src/ox_file.h"
#include "minunit.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int tests_run = 0;
ox__file_t file_handle;

const char test_dataset[] = "test_dataset";
const int num_pages = 100;

static char *test_page_write() {
	mu_assert("ERROR(file_create): unable to create file.", 
		0 == ox__file_create(&file_handle, test_dataset));

	char *page_content = malloc(PAGE_SIZE);
	int size_of_int = sizeof(int);
	const int M = PAGE_SIZE / size_of_int;

	// Save page 0~99; on each page, save 1,2,...,n
	for (int j = 0; j < num_pages; j++) {
		for (int i = 0; i < M; i++) {
			*(int *)(page_content + i * size_of_int) = j;
		}
		mu_assert("ERROR(page_write): unable to save page.",
			0 == ox__save_next_page(&file_handle, page_content));
	}

	// Overwrite page 1; save 2,4,...,2n
	for (int i = 0; i < M; i++) {
		*(int *)(page_content + i * size_of_int) = -1;
	}
	mu_assert("ERROR(page_write): unable to save page.",
		0 == ox__save_page(&file_handle, page_content, 1));

	mu_assert("ERROR(file_close): unable to create file.", 
		0 == ox__file_close(&file_handle));
	free(page_content);
	return 0;
}

static char *test_page_read() {
	mu_assert("ERROR(file_open): unable to open file.", 
		0 == ox__file_open(&file_handle, test_dataset, "r"));

	char *page_content = malloc(PAGE_SIZE);
	int size_of_int = sizeof(int);
	const int M = PAGE_SIZE / size_of_int;

	int x;
	for (int j = 0; j < num_pages; j++) {
		mu_assert("ERROR(page_read): unable to read page.", 
			0 == ox__read_next_page(&file_handle, page_content));

		for (int i = 0; i < M; i++) {
			memcpy((void *)&x, page_content + i * size_of_int, size_of_int);
			if (j != 1) {
				mu_assert("ERROR(page_read): readback value does not equal written value.",
					x == j);
			}
			else {
				mu_assert("ERROR(page_read): readback value does not equal written value.",
					x == -1);
			}
		}
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

