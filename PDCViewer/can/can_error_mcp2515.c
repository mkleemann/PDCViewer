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
 * \file can_error_mcp2515.c
 *
 * \date Created: 18.07.2012 18:23:45
 * \author Matthias Kleemann
 **/


#include "can_mcp2515.h"



/**
 * @brief  get error state of CAN bus
 * @param  chip - select chip to use
 * @return error state
 *
 * \todo Add error detection logic.
 */
can_error_t can_get_bus_errors(eChipSelect chip)
{
   can_error_t error = CAN_ERR_NO_ERROR;

   return error;
}

