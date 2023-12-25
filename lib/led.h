/**
 * Programme qui encapsule les opérations permettant
 * de contrôler la LED du robot.
 * \file led.h
 * Output: Les pins seront déterminés par l'utilisateur lors
 * de l'utilisation de la méthode initialize.
 * Input: Aucune.
 */

#pragma once

#include "register.h"

class Led
{
public:
    static void initialize(volatile uint8_t* modePort,
                           volatile uint8_t* port,
                           uint8_t           pinGreen,
                           uint8_t           pinRed);
    static void setColor(Color color);

private:
    static volatile uint8_t* port_;
    static uint8_t           pinGreen_;
    static uint8_t           pinRed_;
};
