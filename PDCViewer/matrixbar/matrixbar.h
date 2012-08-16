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

/**
 * \brief type for row/column port access
 */
typedef struct { //! pointer of data direction register
                 pvuint8_t ddr;
                 //! pointer to port register
                 pvuint8_t port;
                 //! port pins to be used
                 uint8_t   pins;
               } matrixPort_t;

/***************************************************************************/
/* PROTOTYPES                                                              */
/***************************************************************************/

/**
 * \brief initialize bargraph hardware and control structs
 */
void matrixbar_init(void);

/**
 * \brief set bargraph to defined maximum value for column specified
 * \param whichColumn - column to use to set row to max
 */
void matrixbar_set_max(uint8_t whichColumn);

/**
 * \brief set bargraph to any value
 * \param value - value within range to be set
 * \param whichColumn - column to use to set row to max
 */
void matrixbar_set(uint16_t value, uint8_t whichColumn);

/**
 * \brief clear bargraph
 * \param whichColumn - column to use to set row to max
 */
void matrixbar_clear(uint8_t whichColumn);

/**
 * \brief calculate pins to be set
 * @param value - value to be calculated/matched within pins to use
 * @return port value to be used directly on port pins
 */
uint8_t matrixbar_calc_pins(uint8_t value);

/**
 * \brief init columns (chip select)
 */
void matrixbar_init_cols(void);

/**
 * \brief set column(s)
 * \param whichColumn - column to use to set row to max
 *
 * This is done either set to HIGH level or LOW level, if inverted.
 *
 */
void matrixbar_set_col(uint8_t whichColumn);

/**
 * \brief reset column(s)
 * \param whichColumn - column to use to set row to max
 *
 * This is done either set to LOW level or HIGH level, if inverted.
 */
void matrixbar_reset_col(uint8_t whichColumn);

#endif /* MATRIXBAR_H_ */