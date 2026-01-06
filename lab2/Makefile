TOOLCHAIN_PREFIX ?= riscv64-unknown-elf-

CC := $(TOOLCHAIN_PREFIX)gcc
AS := $(TOOLCHAIN_PREFIX)as
LD := $(TOOLCHAIN_PREFIX)gcc

CFLAGS := -g -march=rv32im -mabi=ilp32 -ffreestanding -nostdlib -Iinc -O0 -fno-stack-protector
ASFLAGS := -g -march=rv32im -mabi=ilp32
LDFLAGS := -g -march=rv32im -mabi=ilp32 -ffreestanding -nostdlib -T linker.ld

# Shared objects (used by all parts)
COMMON_OBJS := build/start.o build/utils.o

# Part-specific objects (each part has .c and .S)
PART1_OBJS := $(COMMON_OBJS) build/part1.o build/part1_asm.o
PART2_OBJS := $(COMMON_OBJS) build/part2.o build/part2_asm.o
PART3_OBJS := $(COMMON_OBJS) build/part3.o build/part3_asm.o
PART4_OBJS := $(COMMON_OBJS) build/part4.o build/part4_asm.o

.PHONY: all clean part1 part2 part3 part4

all: part1 part2 part3 part4

part1: build/part1
part2: build/part2
part3: build/part3
part4: build/part4

# Assembly files
build/%.o: src/%.S
	@mkdir -p build
	@echo "  AS    $<"
	@$(AS) $(ASFLAGS) $< -o $@

# C files
build/%.o: src/%.c
	@mkdir -p build
	@echo "  CC    $<"
	@$(CC) $(CFLAGS) -c $< -o $@

# Link each part
build/part1: $(PART1_OBJS) linker.ld
	@echo "  LD    $@"
	@$(LD) $(LDFLAGS) $(PART1_OBJS) -o $@ -lgcc

build/part2: $(PART2_OBJS) linker.ld
	@echo "  LD    $@"
	@$(LD) $(LDFLAGS) $(PART2_OBJS) -o $@ -lgcc

build/part3: $(PART3_OBJS) linker.ld
	@echo "  LD    $@"
	@$(LD) $(LDFLAGS) $(PART3_OBJS) -o $@ -lgcc

build/part4: $(PART4_OBJS) linker.ld
	@echo "  LD    $@"
	@$(LD) $(LDFLAGS) $(PART4_OBJS) -o $@ -lgcc

clean:
	rm -rf build