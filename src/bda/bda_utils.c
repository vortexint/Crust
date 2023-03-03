#include "./bda_utils.h"

uint16_t detect_bios_area_hardware(void)
{
    const uint16_t* bda_detected_hardware_ptr = (const uint16_t*) 0x410;
    return *bda_detected_hardware_ptr;
}
 
enum video_type get_bios_area_video_type(void)
{
    return (enum video_type) (*((const uint16_t*) 0x410) & 0x30);
}

uint16_t get_bda_ram(void)
{
    const uint16_t* bda_ram_ptr = (const uint16_t*) 0x413;
    return *bda_ram_ptr;
}