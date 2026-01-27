TOOL = riscv64-unknown-elf-
BUILD_DIR = build

COMMON_FLAGS = -march=rv32im -mabi=ilp32 \
               -nostdlib -nostartfiles -ffreestanding \
               -O0 -fno-builtin -fno-inline

.PHONY: part1 part2 part3 clean

part1: $(BUILD_DIR)/part1/main.mem
part2: $(BUILD_DIR)/part2/main.mem
part3: $(BUILD_DIR)/part3/main.mem

$(BUILD_DIR)/%/main.mem: %/*.c %/*.S %/link.ld
	@mkdir -p $(BUILD_DIR)/$*
	$(TOOL)gcc $(COMMON_FLAGS) \
		-I$* \
		-T $*/link.ld \
		-o $(BUILD_DIR)/$*/main.elf \
		$*/boot.S \
		$*/fuzz_helper.S \
		$*/crt0.S \
		$*/serial.c \
		$*/utils.c \
		$*/exception_handler.c \
		$*/shd_main.c
	$(TOOL)objdump -d -s -x $(BUILD_DIR)/$*/main.elf > $(BUILD_DIR)/$*/main.dump
	$(TOOL)objcopy -O binary $(BUILD_DIR)/$*/main.elf $(BUILD_DIR)/$*/main.bin
	xxd -b -c 4 $(BUILD_DIR)/$*/main.bin | awk '{print $$2 "\n" $$3 "\n" $$4 "\n" $$5}' > $@
	rm $(BUILD_DIR)/$*/main.bin
	@echo "Built: $@"

clean:
	rm -rf $(BUILD_DIR)