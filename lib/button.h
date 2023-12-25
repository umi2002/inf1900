/** 
 * Programme qui encapsule les opérations permettant
 * de contrôler l'interrupteur du robot. Il permet
 * l'interruptionn par scrutation ainsi que par interrupton.
 * \file button.h
 * Output: Aucune.
 * Input: Pin de l'interrupteur branché sur le pin D2.
 */

#pragma once
#include "register.h"

class Button
{
public:
    static void initialize();
    static bool isPressed();
    static bool isClicked();
    static void enableInterrupt();

private:
    static volatile uint8_t* port_;
       static const uint8_t  buttonPin_;
                static bool  wasPressedState_;
};
