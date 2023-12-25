#pragma once

#include "memoire_24.h"

class Vector
{
public:
    Vector(uint8_t address);
    Vector(const Vector& other);
    ~Vector();
    void    push_back(uint8_t data);
    void    pop_back();
    uint8_t getSize();
    uint8_t getStartingAddress();
    uint8_t getData(uint8_t index);
    void    writeData(uint8_t index, uint8_t data);
    uint8_t top();
    bool    empty();

private:
    uint8_t startingAddress_;
    uint8_t currentAddress_;
    uint8_t size_ = 0;
};
