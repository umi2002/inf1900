#pragma once

#include "led.h"
#include "memoire_24.h"
#include "sound.h"
#include "wheels.h"

const uint8_t COMMANDS_START_ADDRESS = 2;
const uint8_t BYTE_LENGTH            = 8;

class Robot
{
public:
    static void initialize();

    static uint16_t getTotalAdrresses();

    static void loadListCommands(uint8_t listCommands[], const uint16_t nBytes);

    static void loadCommand();

    static void execCommand();

private:
    static uint8_t* listCommands_;
    static uint16_t address_;
    static uint8_t  instruction_;
    static uint8_t  operand_;
    static bool     isStarted_;
};
