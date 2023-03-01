#include "graphics/vga_text.h"

void c_main() {
    Writer writer;
    writer.buffer = (Buffer*) 0xb8000;
    writer.color_code = ColorCode_new(Black, White);
    writer.column_position = 0;
    write_string(&writer, "Hello world\n");
}

void os_main() {
    c_main();
}