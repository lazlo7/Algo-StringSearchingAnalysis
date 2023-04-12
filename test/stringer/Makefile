CC=g++
CFLAGS=-Wall -Wextra -pedantic -std=c++20

SRC_DIR=../../src/stringer
SEARCHER_DIR=$(SRC_DIR)/searcher
SEARCHER_INCLUDE=$(SEARCHER_DIR)/searcher.cpp

searcher_test: 
	$(CC) $(CFLAGS) searcher_test.cpp -o searcher_test.out $(SEARCHER_DIR)/naive_searcher.cpp $(SEARCHER_DIR)/kmp_searcher.cpp $(SEARCHER_INCLUDE) -g

wildcards_searcher_test:
	$(CC) $(CFLAGS) wildcards_searcher_test.cpp -o wildcards_searcher_test.out $(SEARCHER_DIR)/naive_searcher.cpp $(SEARCHER_DIR)/kmp_searcher.cpp $(SEARCHER_INCLUDE) -g

split_by_wildcard_test:
	$(CC) $(CFLAGS) split_by_wildcard_test.cpp -o split_by_wildcard_test.out $(SEARCHER_DIR)/kmp_searcher.cpp $(SEARCHER_INCLUDE) -g

clean:
	rm -f *.out
