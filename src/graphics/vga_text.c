#include "./vga_text.h"

ColorCode ColorCode_new(Color foreground, Color background) {
    return (background << 4) | foreground; // if background is 8 bits and foreground is 4 bits
}

void write_byte(Writer* writer, unsigned char byte) {
    if (byte == '\n') {
        writer->column_position = 0;
    } else {
        if (writer->column_position >= BUFFER_WIDTH) {
            writer->column_position = 0;
        }

        unsigned int row = BUFFER_HEIGHT - 1;
        unsigned int col = writer->column_position;

        ColorCode color_code = writer->color_code;
        writer->buffer->chars[row][col].ascii_character = byte;
        writer->buffer->chars[row][col].color_code = color_code;
        writer->column_position += 1;
    }
}

void write_string(Writer* writer, const char* string) {
    for (int i = 0; string[i] != '\0'; i++) {
        unsigned char byte = string[i];
        if (byte >= 0x20 && byte <= 0x7e || byte == '\n') {
            write_byte(writer, byte);
        } else {
            write_byte(writer, 0xfe);
        }
    }
}

void new_line(Writer* writer) {
    for (int row = 1; row < BUFFER_HEIGHT; row++) {
        for (int col = 0; col < BUFFER_WIDTH; col++) {
            ScreenChar character = writer->buffer->chars[row][col];
            writer->buffer->chars[row - 1][col] = character;
        }
    }
    clear_row(writer, BUFFER_HEIGHT - 1);
    writer->column_position = 0;
}

//void clear_row(Writer* writer, unsigned int row) {
//    for (int col = 0; col < BUFFER_WIDTH; col++) {
//        ScreenChar character = {0, writer->color_code};
//        writer->buffer->chars[row][col] = character;
//    }
//}

void clear_row(Writer* writer, unsigned int row) {
    ScreenChar blank = {
        .ascii_character = ' ',
        .color_code = writer->color_code
    };
    for (int col = 0; col < BUFFER_WIDTH; col++) {
        writer->buffer->chars[row][col] = blank;
    }
}