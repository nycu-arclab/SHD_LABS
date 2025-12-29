# RISC-V Assembly Warmup Recitation
# Joseph Ravichandran
# MIT Secure Hardware Design Spring 2023
#
# MIT License
# Copyright (c) 2022-2023 Joseph Ravichandran
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

TOOLCHAIN_PREFIX ?= riscv64-unknown-elf-

CC := $(TOOLCHAIN_PREFIX)gcc
AS := $(TOOLCHAIN_PREFIX)as
LD := $(TOOLCHAIN_PREFIX)gcc

CFLAGS := -g -march=rv32im -mabi=ilp32 -ffreestanding -nostdlib -Iinc -O0
ASFLAGS := -g -march=rv32im -mabi=ilp32
LDFLAGS := -g -march=rv32im -mabi=ilp32 -ffreestanding -nostdlib -T linker.ld

TARGET := build/simple
OBJECTS := build/start.o build/utils.o build/compute.o build/simple.o

.PHONY: all clean

all: $(TARGET)

build/%.o: src/%.S
	@mkdir -p build
	@echo "  AS    $<"
	@$(AS) $(ASFLAGS) $< -o $@

build/%.o: src/%.c
	@mkdir -p build
	@echo "  CC    $<"
	@$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJECTS) linker.ld
	@echo "  LD    $@"
	@$(LD) $(LDFLAGS) $(OBJECTS) -o $@ -lgcc

clean:
	rm -rf build