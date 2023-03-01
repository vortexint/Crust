#ifndef VGA_TEXT_H
#define VGA_TEXT_H

#define BUFFER_HEIGHT 25
#define BUFFER_WIDTH 80

typedef enum {
    Black,
    Blue,
    Green,
    Cyan,
    Red,
    Magenta,
    Brown,
    LightGray,
    DarkGray,
    LightBlue,
    LightGreen,
    LightCyan,
    LightRed,
    Pink,
    Yellow,
    White
} Color;

typedef unsigned char ColorCode;

typedef struct {
    unsigned char ascii_character;
    ColorCode color_code;
} ScreenChar;

typedef struct {
    ScreenChar chars[BUFFER_HEIGHT][BUFFER_WIDTH];
} Buffer;

typedef struct {
    unsigned int column_position;
    ColorCode color_code;
    Buffer* buffer;
} Writer;

ColorCode ColorCode_new(Color foreground, Color background);
void clear_row(Writer* writer, unsigned int row);
void newline(Writer* writer);
void write_byte(Writer* writer, unsigned char byte);
void write_string(Writer* writer, const char* string);

#endif