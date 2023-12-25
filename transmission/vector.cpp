#include "vector.h"

Vector::Vector()
{
    Memoire24CXXX::initialize();
}

Vector::~Vector() { }

void Vector::push_back(uint8_t data)
{
    Memoire24CXXX::ecriture(currentAddress, data);
    currentAddress++;
    size++;
}

void Vector::pop_back()
{
    currentAddress--;
    size--;
}

uint8_t Vector::getSize()
{
    return size;
}

uint8_t Vector::getData(uint8_t index)
{
    uint8_t data = 0;
    Memoire24CXXX::lecture(index, &data);
    return data;
}

void Vector::writeData(uint8_t index, uint8_t data)
{
    Memoire24CXXX::ecriture(index, data);
}
