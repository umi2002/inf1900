#include "vector.h"

Vector::Vector(uint8_t address) :
    startingAddress_(address),
    currentAddress_(address)
{ }

Vector::Vector(const Vector& other) :
    startingAddress_(other.startingAddress_),
    currentAddress_(other.currentAddress_),
    size_(other.size_)
{ }

Vector::~Vector() { }

void Vector::push_back(uint8_t data)
{
    Memoire24CXXX::ecriture(currentAddress_, data);
    currentAddress_++;
    size_++;
}

void Vector::pop_back()
{
    currentAddress_--;
    size_--;
}

uint8_t Vector::getSize()
{
    return size_;
}

uint8_t Vector::getStartingAddress()
{
    return startingAddress_;
}

uint8_t Vector::getData(uint8_t index)
{
    uint8_t data = 0;
    Memoire24CXXX::lecture(index + startingAddress_, &data);
    return data;
}

void Vector::writeData(uint8_t index, uint8_t data)
{
    Memoire24CXXX::ecriture(index + startingAddress_, data);
}

uint8_t Vector::top()
{
    return getData(getSize());
}

bool Vector::empty()
{
    return getSize() == 0;
}
