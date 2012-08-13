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
 * \file matrixbar.c
 *
 * \date Created: 04.02.2012 21:19:14
 * \author Matthias Kleemann
 **/


#include <avr/io.h>
#include "../util/util.h"
#include "matrixbar.h"

/***************************************************************************/
/* FUNCTIONS                                                               */
/***************************************************************************/

/**
 * @brief initialize bargraph hardware and control structs
 */
void matrixbar_init()
{
   // initialize bargraph port pins to output, low
   for(int i = P_MATRIXBAR_OFFSET; i < P_MATRIXBAR_RANGE+P_MATRIXBAR_OFFSET; ++i)
   {
      EXP_PORT(P_MATRIXBAR) &= ~(1 << i);
      EXP_DDR(P_MATRIXBAR)  |=  (1 << i);
   }

   // initialize chip select, if defined
   matrixbar_init_cs();
}

/**
 * @brief set bargraph to defined maximum value
 */
void matrixbar_set_max(void)
{
   uint8_t mask = ~0;
   matrixbar_set_cs();
   EXP_PORT(P_MATRIXBAR) |= ~(mask << P_MATRIXBAR_RANGE);
   matrixbar_reset_cs();
}

/**
 * @brief set bargraph to any value
 * @param value - value within range to be set
 */
void matrixbar_set(uint8_t value)
{
   // remove old values
   matrixbar_clear();
   matrixbar_set_cs();
   EXP_PORT(P_MATRIXBAR) |= matrixbar_calc_pins(value);
   matrixbar_reset_cs();
}

/**
 * @brief clear bargraph
 */
void matrixbar_clear(void)
{
   uint8_t mask = ~0;
   matrixbar_set_cs();
   EXP_PORT(P_MATRIXBAR) &= (mask << P_MATRIXBAR_RANGE);
   matrixbar_reset_cs();
}

/**
 * @brief calculate pins to be set
 * @param value - value to be calculated/matched within pins to use
 * @return port value to be used directly on port pins
 */
uint8_t matrixbar_calc_pins(uint8_t value)
{
   uint8_t retVal = 0;
   uint8_t mask   = ~0;
   // divide range with maximum and multiply value to get bargraph steps
#ifdef MATRIXBAR_REVERSE
   uint8_t step = (P_MATRIXBAR_RANGE * (MATRIXBAR_MAX_VALUE - value + 1) / MATRIXBAR_MAX_VALUE);
#else
   uint8_t step = (P_MATRIXBAR_RANGE * value / MATRIXBAR_MAX_VALUE);
#endif
   // setup next value, but keep values > MAX out
   if(value <= MATRIXBAR_MAX_VALUE)
   {
#ifdef MATRIXBAR_INVERTED
      // mask out unused bits
      retVal |= (mask << step) & ~(mask << P_MATRIXBAR_RANGE);
#else
      retVal |= ~(mask << step);
#endif
   }

   // add defined offset
   retVal <<= P_MATRIXBAR_OFFSET;

   return retVal;
}


/**
 * @brief init chip select, if available
 */
void matrixbar_init_cs(void)
{
#ifdef P_MATRIXBAR_CS
   // set initial value of chip select port pin
#ifdef P_MATRIXBAR_CS_INVERTED
   SET_PIN(P_MATRIXBAR_CS);
#else
   RESET_PIN(P_MATRIXBAR_CS);
#endif
   // setup pin bahaviour
   PIN_SET_OUTPUT(P_MATRIXBAR_CS);
#endif
}

/**
 * @brief set chip select, if available
 *
 * This is done either set to HIGH level or LOW level, if inverted.
 */
void matrixbar_set_cs(void)
{
#ifdef P_MATRIXBAR_CS
#ifdef P_MATRIXBAR_CS_INVERTED
   RESET_PIN(P_MATRIXBAR_CS);
#else
   SET_PIN(P_MATRIXBAR_CS);
#endif
#endif
}

/**
 * @brief reset chip select, if available
 *
 * This is done either set to LOW level or HIGH level, if inverted.
 */
void matrixbar_reset_cs(void)
{
#ifdef P_MATRIXBAR_CS
#ifdef P_MATRIXBAR_CS_INVERTED
   SET_PIN(P_MATRIXBAR_CS);
#else
   RESET_PIN(P_MATRIXBAR_CS);
#endif
#endif
}

