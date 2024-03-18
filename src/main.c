#include "stdafx.h"
#include "graphics/vga_text.h"
#include "bda/bda_utils.h"
#include "compile_time.h"

#define STR(x) #x
static bool vga_output = true;

#define __OS_VERSION__ "0.1"

void c_main() {
    Writer writer;
    writer.buffer = (Buffer*) 0xb8000;
    writer.color_code = ColorCode_new(Yellow, Black);
    writer.column_position = 0;
    
    write_string(&writer, "Welcome to ");
    writer.color_code = ColorCode_new(Green, Black);
    write_string(&writer, "Crust");
    writer.color_code = ColorCode_new(Yellow, Black);
    write_string(&writer, "!");
    writer.color_code = ColorCode_new(White, Black);
    newline(&writer);
    write_string(&writer, "Version: ");
    writer.color_code = ColorCode_new(LightCyan, Black);
    write_string(&writer, __OS_VERSION__);
    writer.color_code = ColorCode_new(White, Black);
    write_string(&writer, " Build date: ");
    writer.color_code = ColorCode_new(LightCyan, Black);
    write_string(&writer, __DATE__);
    writer.color_code = ColorCode_new(White, Black);
    newline(&writer);
    write_string(&writer, "--------------------------------------------------------------------------------");
    newline(&writer);
    write_string(&writer, "Display type: ");
    switch (get_bios_area_video_type()) {
    case 0x20:
        write_string(&writer, "Color");
        break;
    case 0x30:
        write_string(&writer, "Monochrome");
        break;
    default:
        write_string(&writer, "Unknown");
        break;
    }
    newline(&writer);
    //write_string(&writer, "RAM: ");
}