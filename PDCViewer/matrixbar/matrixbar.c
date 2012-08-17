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
/* GLOBALS                                                                 */
/***************************************************************************/

/**
 * \brief port access to rows
 */
matrixPort_t   row[MATRIXBAR_NUM_ROWS]          = { P_MATRIXBAR_ROW };

/**
 * \brief port access to columns
 */
matrixPort_t   column[MATRIXBAR_NUM_COLS]       = { P_MATRIXBAR_COL };

/**
 * \brief number of pins in a row defined
 */
uint16_t       numPinsInRow                     = 0;

/**
 * \brief number of pins in a columns defined
 */
uint16_t       numPinsInCol                     = 0;

/**
 * \brief columns indexed
 *
 * To access a column simply by a number a mask for port/pin combination
 * needs to be known. This is set up in this array.
 *
 * The maximum index is determined of number of ports used and the maximum
 * of 8 pins per port on a regular ATmega (MATRIXBAR_NUM_COLS * 8).
 */
matrixColumn_t columnIdx[MATRIXBAR_NUM_COLS * 8];


/***************************************************************************/
/* FUNCTIONS                                                               */
/***************************************************************************/

/**
 * \brief initialize bargraph hardware and control structs
 */
void matrixbar_init()
{
   int i, j;
   // initialize bargraph port pins to output, low
   // rows
   for(i = 0; i < MATRIXBAR_NUM_ROWS; ++i)
   {
      *(row[i].port) &= ~(row[i].pins);
      *(row[i].ddr)  |= row[i].pins;
      for(j = 0; j < 8; ++j)
      {
         if(1 == ((row[i].pins >> j) & 0x01))
         {
            ++numPinsInRow;
         }
      }
   }
   // columns
   for(i = 0; i < MATRIXBAR_NUM_COLS; ++i)
   {
#ifdef P_MATRIXBAR_COL_INVERTED
      *(column[i].port) |= column[i].pins;
#else
      *(column[i].port) &= ~(column[i].pins);
#endif
      *(column[i].ddr)  |= column[i].pins;
      for(j = 0; j < 8; ++j)
      {
         if(1 == (column[i].pins & (1 << j)))
         {
            columnIdx[numPinsInCol].idx   = i;
            columnIdx[numPinsInCol].mask  = (1 << j);
            ++numPinsInCol;
         }
      }
   }
}

/**
 * \brief set bargraph to defined maximum value for column specified
 */
void matrixbar_set_max(void)
{
   int i;

   for(i = 0; i < MATRIXBAR_NUM_ROWS; ++i)
   {
      *(row[i].port) |= row[i].pins;
   }
}

/**
 * \brief set bargraph to any value
 * \param value - value within range to be set
 */
void matrixbar_set(uint16_t value)
{
   // remove old values
   matrixbar_clear();
#if 0
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
#endif
}

/**
 * \brief clear bargraph
 */
void matrixbar_clear()
{
   int i;

   for(i = 0; i < MATRIXBAR_NUM_ROWS; ++i)
   {
      *(row[i].port) &= ~(row[i].pins);
   }
}


/**
 * \brief set column(s)
 * \param whichColumn - column to use to set row to max
 *
 * This is done either set to HIGH level or LOW level, if inverted.
 *
 */
void matrixbar_set_col(uint8_t whichColumn)
{
#ifdef P_MATRIXBAR_COL_INVERTED
   *(column[columnIdx[whichColumn].idx].port) &= ~(columnIdx[whichColumn].mask);
#else
   *(column[columnIdx[whichColumn].idx].port) |= (columnIdx[whichColumn].mask);
#endif
}

/**
 * \brief reset column(s)
 * \param whichColumn - column to use to set row to max
 *
 * This is done either set to LOW level or HIGH level, if inverted.
 */
void matrixbar_reset_col(uint8_t whichColumn)
{
#ifdef P_MATRIXBAR_COL_INVERTED
   *(column[columnIdx[whichColumn].idx].port) |= (columnIdx[whichColumn].mask);
#else
   *(column[columnIdx[whichColumn].idx].port) &= ~(columnIdx[whichColumn].mask);
#endif
}

