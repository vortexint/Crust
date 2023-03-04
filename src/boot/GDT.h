#ifndef GDT_H
#define GDT_H

#include <stdint.h>

void encodeGdtEntry(uint8_t *target, struct GDT source);

#endif