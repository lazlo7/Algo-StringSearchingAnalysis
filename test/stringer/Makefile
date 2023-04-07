CC=g++
CFLAGS=-Wall -Wextra -pedantic -std=c++20

SRC_DIR=../../src/stringer
SEARCHER_DIR=$(SRC_DIR)/searcher
SEARCHER_INCLUDE=$(SEARCHER_DIR)/searcher.cpp

naive_searcher_test: 
	$(CC) $(CFLAGS) naive_searcher_test.cpp -o naive_searcher_test.out $(SEARCHER_DIR)/naive_searcher.cpp $(SEARCHER_INCLUDE)

clean:
	rm -f *.out
