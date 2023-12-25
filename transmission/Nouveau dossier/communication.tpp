#pragma once
#include "communication.h"

template <typename T>
void Communication::transmitUART(T data)
{
    while (!Register::areBitsSet(&UCSR0A, UDRE0));
    UDR0 = data; 
}

template <typename T>
void Communication::transmitUART(T data[])
{
    uint16_t dataLength = 0;
        while (data[dataLength] != '\0')
            dataLength++;
        
    for (uint16_t i = 0; i < dataLength ; i++)
    {
        while (!Register::areBitsSet(&UCSR0A, UDRE0));
        UDR0 = data[i];
    }
}

template <typename... T>
void Communication::transmitUART(T... data)
{
    (transmitUART(data), ...);
}