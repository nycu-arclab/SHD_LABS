#!/bin/bash
source config.sh

# Connect GDB to QEMU
gdb-multiarch \
    -ex "set architecture riscv:rv32" \
    -ex "target remote $DEBUG_HOST:$DEBUG_PORT" \
    -ex "set disassemble-next-line on" \
    "$TARGET"