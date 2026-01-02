// copyright

#ifndef QEMU_VIRT
#define QEMU_VIRT

// The UART0 base address
#define QEMU_VIRT_UART ((0x10000000))

// The line status register
#define QEMU_VIRT_UART_LSR ((0x10000005))

// See 16550 UART datasheet: http://caro.su/msx/ocm_de1/16550.pdf
#define UART_LSR_DATA_READY_MASK ((0x01))

#define SERIAL_NEWLINE ((0x0D))
#define NEWLINE ((0x0A))

#endif // QEMU_VIRT
