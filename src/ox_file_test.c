#include "../src/ox_file.h"
#include "minunit.h"

#include <stdint.h>
#include <stdio.h>

int tests_run = 0;
char test_dataset[] = "test_dataset";
ox__file_t file_handle;

static char *test_file_create() {
	mu_assert("ERROR(file_create): unable to create file.", 
		0 == ox__file_create(&file_handle, test_dataset));
	if (file_handle.fptr != NULL) {
		fclose(file_handle.fptr);
	}
	mu_assert("ERROR(file_create): should not create file if it exists.", 
		-1 == ox__file_create(&file_handle, test_dataset));
	return 0;
}

static char *test_file_open() {
	mu_assert("ERROR(file_open): unable to open file.", 
		0 == ox__file_open(&file_handle, test_dataset));
	return 0;
}

static char *test_file_close() {
	mu_assert("ERROR(file_close): unable to close file.", 
		0 == ox__file_close(&file_handle));
	return 0;
}

static char *test_file_destroy() {
	mu_assert("ERROR(file_destroy): unable to destroy file.", 
		0 == ox__file_destroy(test_dataset));
	return 0;
}

static char *all_tests() {
 	mu_run_test(test_file_create);
  	mu_run_test(test_file_open);
  	mu_run_test(test_file_close);
  	mu_run_test(test_file_destroy);
  	return 0;
}

int main(void) {
	ox__file_destroy(test_dataset);

  	char *result = all_tests();
  	if (result != 0) {
    	printf("%s\n", result);
  	}
  	else {
    	printf("ALL TESTS in file_test PASSED\n");
  	}

  	return 0;
}

