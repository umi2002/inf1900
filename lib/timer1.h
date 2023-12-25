#pragma once

#include "register.h"

class Timer1
{
public:
    static void initialize();
    static void switchToCtc(uint16_t periodA, uint16_t periodB = 0);
    static void switchToPwm(float periodA, float periodB = 0);
};