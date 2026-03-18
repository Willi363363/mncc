#!/bin/bash

if [ $# -ne 1 ]; then
    echo "USAGE: $0 <asm_file>"
    exit 1
fi

INPUT_FILE="$1"
if [ ! -f "$INPUT_FILE" ]; then
    echo "Error: File '$INPUT_FILE' not found"
    exit 1
fi

DIRNAME="$(dirname "$INPUT_FILE")"
BASENAME="$(basename "$INPUT_FILE" .asm)"
OBJECT_FILE="${DIRNAME}/${BASENAME}.o"
OUTPUT_BINARY="${DIRNAME}/${BASENAME}.out"

nasm -f elf64 "$INPUT_FILE" -o "$OBJECT_FILE" || exit 1
if ! nm -g --defined-only "$OBJECT_FILE" | grep -q "\<_start\>"; then
    echo "Error: entry symbol _start not found in $INPUT_FILE" >&2
    rm -f "$OBJECT_FILE"
    exit 1
fi
ld -e _start -o "$OUTPUT_BINARY" "$OBJECT_FILE" || {
    rm -f "$OBJECT_FILE"
    exit 1
}
rm -f "$OBJECT_FILE"
exit 0