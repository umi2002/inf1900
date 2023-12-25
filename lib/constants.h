/**
 * Programme qui contient les libraries standards et
 * les macros nécessaires pour la programmation du
 * micronctrôleur. Il contient aussi les constantes
 * globales utilisés à travers les fichiers sources.
 * \file constants.h
 */

#pragma once

#define F_CPU 8000000UL
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <util/delay.h>
#include <util/twi.h>

namespace bits
{
    const uint8_t SET   = 0xff;
    const uint8_t CLEAR = 0x00;
}  //namespace bits

namespace max
{
    const uint8_t PWM_VALUE       = 255;
    const uint8_t SPEED           = 100;
    const uint8_t AVAILABLE_NOTES = 37;
}  //namespace max

namespace min
{
    const uint8_t NULL_SPEED = 0;
}

namespace conversion
{
    const uint8_t  TO_PERCENTAGE = 100;
    const uint8_t  OPERAND_TO_MS = 25;
    const uint16_t MS_TO_OCR1X   = 3906;
}  //namespace conversion

namespace default_setting
{
    const uint8_t  BAUD_RATE     = 0xCF;
    const uint16_t CTC_PRESCALER = 1024;
}  //namespace default_setting

namespace delay
{
    const uint8_t  DEBOUNCING     = 10;
    const uint8_t  GREEN_AMBER    = 8;
    const uint8_t  RED_AMBER      = 2;
    const uint8_t  MEMORY_WRITING = 5;
    const uint16_t ROTATION       = 700;
    const uint16_t STOP           = 500;
    const uint8_t  MS             = 1;
}  //namespace delay

namespace offset
{
    const uint8_t MIDI = 45;
}

enum class Color
{
    RED,
    GREEN,
    AMBER,
    OFF
};
