#include "vector.h"

#include <math.h>

class Area
{
public:
    Area();
    ~Area();
    static uint16_t calculateArea(Vector finalPoles);

private:
    static const uint8_t inchConversion = 121;
    static const uint8_t areaDivisor    = 2;
};
