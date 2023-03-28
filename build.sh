#!/bin/sh

set -xeu

CC="g++"
CFLAGS="-Wall -Wextra -pedantic -std=c++20 -g"
SRC_DIR="src/stringer"
SOURCES="${SRC_DIR}/main.cpp"
OUTPUT="stringer"
OUTPUT_DIR="./build"

mkdir -p $OUTPUT_DIR
$CC $CFLAGS -o $OUTPUT_DIR/$OUTPUT $SOURCES
