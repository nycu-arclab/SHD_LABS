#!/bin/bash
source config.sh

# Check for --debug flag
DEBUG_FLAGS=""
if [[ "$1" == "--debug" ]] || [[ "$2" == "--debug" ]]; then
    DEBUG_FLAGS="-gdb tcp::$DEBUG_PORT -S"
    echo "Waiting for debugger on port $DEBUG_PORT..."
fi

# Run QEMU
qemu-system-riscv32 \
    -machine virt \
    -m 128M \
    -bios none \
    -kernel $TARGET \
    -serial stdio \
    -nographic \
    -monitor none \
    $DEBUG_FLAGS