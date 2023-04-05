#!/bin/sh

set -xeu

CC="g++"
CFLAGS="-Wall -Wextra -pedantic -std=c++20 -O3"
SRC_DIR="src/stringer"
SOURCES="${SRC_DIR}/main.cpp ${SRC_DIR}/tester.cpp ${SRC_DIR}/searcher/naive_searcher.cpp ${SRC_DIR}/text_generator/uniform_text_generator.cpp"
OUTPUT="stringer"
OUTPUT_DIR="./build"

mkdir -p $OUTPUT_DIR
$CC $CFLAGS -o $OUTPUT_DIR/$OUTPUT $SOURCES
