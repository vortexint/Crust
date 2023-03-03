#include <stdint.h>
 
enum video_type
{
    VIDEO_TYPE_NONE = 0x00,
    VIDEO_TYPE_COLOR = 0x20,
    VIDEO_TYPE_MONOCHROME = 0x30,
};
 
uint16_t detect_bios_area_hardware(void);
 
enum video_type get_bios_area_video_type(void);

uint16_t get_bda_ram(void);