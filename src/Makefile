CC = gcc
FLAGS = -ansi -pedantic -std=c99
WARNS = -Wall -Wextra

DEST = \
	ox_file_test \
	ox_page_test

TEST_DATASETS = \
	test_dataset

all: ox_file_test ox_page_test
	
ox_file_test: ox_file.o ox_file_test.c
	$(CC) $(FLAGS) $(WARNS) ox_file.o ox_file_test.c -o ox_file_test

ox_page_test: ox_file.o ox_page_test.c
	$(CC) $(FLAGS) $(WARNS) ox_file.o ox_page_test.c -o ox_page_test

ox_file.o: ox_file.c ox_file.h
	$(CC) $(FLAGS) $(WARNS) ox_file.c -c

clean:
	rm -rf $(DEST) *.o $(TEST_DATASETS)