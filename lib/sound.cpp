#include "sound.h"

void Sound::initialize()
{
    Timer::initialize();
}

void Sound::playNote(uint8_t midi)
{
    Timer::switchToCtc(midiTable_[midi - offset::MIDI]);
}

void Sound::stopSound()
{
    Register::clear(&TCNT2, &TCCR2A, &TCCR2B, &TIMSK2);
}

const uint8_t Sound::midiTable_[max::AVAILABLE_NOTES] = {
    141, 133, 126, 118, 112, 105, 99, 94, 88, 83, 79, 74, 70,
    66,  62,  59,  55,  52,  49,  46, 44, 41, 39, 37, 35, 33,
    31,  29,  27,  26,  24,  23,  21, 20, 19, 18, 17};
