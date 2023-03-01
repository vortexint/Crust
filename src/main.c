#include "std/stdbool.h"
#include "graphics/vga_text.h"

static bool vga_output = true;

#define __OS_VERSION__ "0.1"

void c_main() {
    Writer writer;
    writer.buffer = (Buffer*) 0xb8000;
    writer.color_code = ColorCode_new(White, Black);
    writer.column_position = 0;
    write_string(&writer, "Welcome to ");
    writer.color_code = ColorCode_new(Green, Black);
    write_string(&writer, "Vortex OS");
    writer.color_code = ColorCode_new(White, Black);
    write_string(&writer, "!");
    newline(&writer);
    write_string(&writer, "v");
    write_string(&writer, __OS_VERSION__);
    write_string(&writer, " TS: ");
    write_string(&writer, __TIMESTAMP__);
}