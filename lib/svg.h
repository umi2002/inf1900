#pragma once

#include "area.h"
#include "communication.h"
#include "memoire_24.h"
#include "shape.h"
#include "vector.h"

class SVG
{
public:
    static void transmitString(const char string[], uint32_t size);
    static void calculateCrc32(const char* s, uint32_t n);
    static void transmitSVG();
    static void transmitCrc();
    static void convertToHex(uint32_t value, char buffer[9]);

private:
    static uint32_t       crc_;
    static const uint32_t stringSizes_[13];
    static const char hexDigits_[16];
};
