/* Linker script for QEMU virt machine */

ENTRY(_start);

MEMORY {
    RAM (rwx) : ORIGIN = 0x80000000, LENGTH = 128M
}

SECTIONS {
    . = 0x80000000;

    .text : ALIGN(0x1000) {
        *(.text.init);
        *(.text);
    }

    .rodata : ALIGN(0x1000) {
        *(.rodata);
    }

    .bss : ALIGN(0x1000) {
        *(.bss);
    }

    .data : ALIGN(0x1000) {
        *(.data);
        . = . + 1M;
        _stack_top = .;
    }
}