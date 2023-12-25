/*
 * Programme qui encapsule les opérations permettant
 * d'initialiser la minuterie 1 du robot. Elle permet
 * l'utilisation de la minuterie en mode PWM ainsi
 * qu'en mode CTC.
 * \file timer.h
 * Output: Sortie PWM sur les pins PD4 et PD5.
 * Input: Aucune.
 */

#pragma once

#include "register.h"

class Timer
{
public:
    static void initialize();
    static void switchToCtc(uint8_t outputCompareValueA,
                            uint8_t outputCompareValueB = 0);
    static void switchToPwm(uint8_t outputCompareValueA,
                            uint8_t outputCompareValueB = 0);
};
