#pragma once
#include "register.h"

template <typename... Bit>
bool Register::areBitsSet(volatile uint8_t* registerPtr, Bit... bit)
{
    return ((*registerPtr & (1 << bit)) && ...);
}

template <typename... Bit>
void Register::setBits(volatile uint8_t* registerPtr, Bit... bit)
{
    *registerPtr |= ((1 << bit) | ...);
}

template <typename... Bit>
void Register::clearBits(volatile uint8_t* registerPtr, Bit... bit)
{
    *registerPtr &= ~((1 << bit) | ...);
}

template <typename... T>
void Register::set(volatile T*... registerPtr)
{
    ((*registerPtr = bits::SET), ...);
}

template <typename... T>
void Register::clear(volatile T*... registerPtr)
{
    ((*registerPtr = bits::CLEAR), ...);
}

template <typename... Bit>
void Register::toggleBits(volatile uint8_t* registerPtr, Bit... bit)
{
    ((*registerPtr ^= (1 << bit)), ...);
}
