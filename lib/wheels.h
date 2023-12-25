/**
 * Programme qui encapsule les opérations permettant
 * de contrôler les roues du robot. Il permet l'ajustement
 * de la vitesse des roues ainsi que la direction des roues.
 * \file wheels.h
 * Output: Pin de PWM branché sur les pins B3 et B4 (1 pour chaque roue).
 * Pin de direction branché sur les pins B5 et B6 (1 pour chaque roue).
 * Input: Aucune.
 */

#pragma once

#include "register.h"

class Wheels
{
public:
    static void initialize();
    static void adjustLeft(uint8_t speed);
    static void adjustRight(uint8_t speed);
    static void moveForward(uint8_t speed);
    static void moveBackward(uint8_t speed);
    static void changeDirectionLeft();
    static void changeDirectionRight();
    static void rotateLeft();
    static void rotateRight();

private:
    static volatile uint8_t* outputPort_;
    static const uint8_t     intensityPinLeft_;
    static const uint8_t     intensityPinRight_;
    static const uint8_t     directionPinLeft_;
    static const uint8_t     directionPinRight_;
};
