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

// Can store a single byte of data.
typedef unsigned char ColorCode;

ColorCode ColorCode_new(Color foreground, Color background) {
    return (background << 4) | foreground; // if background is 8 bits and foreground is 4 bits
}

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