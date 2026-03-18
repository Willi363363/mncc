#!/bin/bash

if [ $# -ne 1 ]; then
    echo "USAGE: $0 [c_file]"
    exit 1
fi

INPUT_FILE="$1"
FILENAME=$(basename "$INPUT_FILE" .c)
OBJECT_FILE="${FILENAME}.o"
OUTPUT_BINARY="${FILENAME}"

if [ ! -f "$INPUT_FILE" ]; then
    echo "Error: File '$INPUT_FILE' not found"
    exit 1
fi

./mncc "$INPUT_FILE"
if [ ! -f "output.asm" ]; then
    echo "Error: mncc failed to generate output.asm"
    exit 1
fi

nasm -f elf64 output.asm -o "$OBJECT_FILE"
if [ $? -ne 0 ]; then
    echo "Error: nasm assembly failed"
    rm -f "$OBJECT_FILE"
    exit 1
fi

ld "$OBJECT_FILE" -o "$OUTPUT_BINARY"
if [ $? -ne 0 ]; then
    echo "Error: ld linking failed"
    rm -f "$OBJECT_FILE"
    exit 1
fi

rm -f "$OBJECT_FILE" output.asm
echo "Successfully compiled '$INPUT_FILE' to binary './$OUTPUT_BINARY'"
exit 0