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
 * \file matrixbar.h
 *
 * \date Created: 04.02.2012 21:18:57
 * \author Matthias Kleemann
 **/



#ifndef MATRIXBAR_H_
#define MATRIXBAR_H_

#include "matrixbar_config.h"

/***************************************************************************/
/* TYPEDEFS                                                                */
/***************************************************************************/


/***************************************************************************/
/* PROTOTYPES                                                              */
/***************************************************************************/

/**
 * @brief initialize bargraph hardware and control structs
 */
void matrixbar_init(void);

/**
 * @brief set bargraph to defined maximum value
 */
void matrixbar_set_max(void);

/**
 * @brief set bargraph to any value
 * @param value - value within range to be set
 */
void matrixbar_set(uint8_t value);

/**
 * @brief clear bargraph
 */
void matrixbar_clear(void);

/**
 * @brief calculate pins to be set
 * @param value - value to be calculated/matched within pins to use
 * @return port value to be used directly on port pins
 */
uint8_t matrixbar_calc_pins(uint8_t value);

/**
 * @brief init chip select, if available
 */
void matrixbar_init_cs(void);

/**
 * @brief set chip select, if available
 *
 * This is done either set to HIGH level or LOW level, if inverted.
 */
void matrixbar_set_cs(void);

/**
 * @brief reset chip select, if available
 *
 * This is done either set to LOW level or HIGH level, if inverted.
 */
void matrixbar_reset_cs(void);

#endif /* MATRIXBAR_H_ */