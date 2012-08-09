/**
 * ----------------------------------------------------------------------------
 *
 * "THE ANY BEVERAGE-WARE LICENSE" (Revision 42 - based on beer-ware license):
 * <dev@layer128.net> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a be(ve)er(age) in return. (I don't
 * like beer much.)
 *
 * Matthias Kleemann
 *
 * ----------------------------------------------------------------------------
 *
 * \file PDCViewer.c
 *
 * \date Created: 09.08.2012 18:22:46
 * \author Matthias Kleemann
 **/


#include <stdbool.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/cpufunc.h>
#include <util/delay.h>

#include "util/util.h"
#include "spi/spi.h"
#include "can/can_mcp2515.h"
#include "timer/timer.h"

/**
 * @brief main loop
 *
 * The main loop consists of the FSM and calls all necessary init sequences
 * before entering it. Any error in the init process will result in
 * entering the error state.
 **/
int main(void)
{

}
