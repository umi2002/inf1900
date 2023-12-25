/**
 * Programme qui permet d'afficher dans le terminal
 * des charactères à divers endroit dans le code
 * pour des fins de débogage.
 * \file debug.h
 */

#include "communication.h"

#ifdef DEBUG

#    define DEBUG_INIT()   Communication::initialize()
#    define DEBUG_PRINT(x) Communication::transmitUART(x)

#else

#    define DEBUG_INIT()   void()
#    define DEBUG_PRINT(x) void()

#endif
