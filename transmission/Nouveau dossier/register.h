/**
 * Programme qui encapsule les opérations permettant
 * d'affecter les registres.
 * \file register.h
 */

#pragma once
#include "constants.h"

class Register
{
public:
	template<typename... Bit>
	static bool areBitsSet(volatile uint8_t* registerPtr, Bit... bit);

	template<typename... Bit>
	static void setBits(volatile uint8_t* registerPtr, Bit... bit);

	template<typename... Bit>
	static void clearBits(volatile uint8_t* registerPtr, Bit... bit);

	template<typename... T>
	static void set(volatile T*... registerPtr);

	template<typename... T>
	static void clear(volatile T*... registerPtr);

	template<typename... Bit>
	static void toggleBits(volatile uint8_t* registerPtr, Bit... bit);
};

#include "register.tpp"
