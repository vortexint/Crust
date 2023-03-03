#include <stdbool.h>
#include "graphics/vga_text.h"
#include "bda/bda_utils.h"

#include <stdio.h>
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
    write_string(&writer, "VERSION:");
    write_string(&writer, __OS_VERSION__);
    write_string(&writer, " BUILD TS: ");
    write_string(&writer, __TIMESTAMP__);
    newline(&writer);
    write_string(&writer, "Video Type: ");
    switch (get_bios_area_video_type()) {
    case 0x20:
        write_string(&writer, "Colour");
        break;
    case 0x30:
        write_string(&writer, "Monochrome");
        break;
    default:
        write_string(&writer, "Unknown");
        break;
    }
    write_string(&writer, "RAM: ");
    write_string(&writer, 32);
}