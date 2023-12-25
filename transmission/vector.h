#pragma once

#include "memoire_24.h"

class Vector
{
public:
    Vector();
    ~Vector();
    void    push_back(uint8_t data);
    void    pop_back();
    uint8_t getSize();
    uint8_t getData(uint8_t index);
    void    writeData(uint8_t index, uint8_t data);

private:
    uint8_t currentAddress = 140;
    uint8_t size           = 0;
};
