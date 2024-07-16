/* 64 bit version of the SpecOS kernel.
 * Copyright (C) 2024 Jake Steinburger under the MIT license. See the GitHub repository for more information.
 */

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

#include "limine.h"

#include "drivers/include/serial.h"
#include "drivers/include/vga.h"
#include "sys/include/gdt.h"
#include "sys/include/idt.h"
#include "drivers/include/keyboard.h"
#include "drivers/include/rtc.h"
#include "drivers/include/disk.h"
#include "utils/include/string.h"
#include "include/shell.h"
#include "utils/include/printf.h"

void _start() {
    // Just send output to a serial port to test
    init_serial();
    initVGA();
    writestring("Trying to initialise GDT...\n");
    initGDT();
    writestring("\nGDT successfully initialised! (as far as can be told. All I know is that there isn't a gpf.)");
    writestring("\n\nTrying to initialise IDT & everything related...\n");
    initIDT();
    char buffer[9];
    uint64_to_hex_string(268419072, buffer);
    printf("\nTEST: Number in hex is 0x%s\n", buffer);
    test_userspace();
    for (;;);
}
