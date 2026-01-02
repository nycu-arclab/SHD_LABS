# copyright



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