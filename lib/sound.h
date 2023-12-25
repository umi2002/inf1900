#pragma once
#include "timer.h"

class Sound
{
public:
    static void initialize();
    static void playNote(uint8_t midi);
    static void stopSound();

private:
    static const uint8_t midiTable_[max::AVAILABLE_NOTES];
};
