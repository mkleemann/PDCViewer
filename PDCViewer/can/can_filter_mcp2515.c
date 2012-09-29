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
 * \file can_filter_mcp2515.c
 *
 * \date Created: 28.11.2011 18:37:21
 * \author Matthias Kleemann
 **/


#include "can_mcp2515.h"

/**
 * @brief clear filters
 * @param chip - select chip to use
 *
 * \note
 * The MCP2515 has to be in configuration mode to set these registers. The
 * function uses sequential write mode to save time and program size.
 *
 */
void clear_filters(eChipSelect chip)
{
   uint8_t data[12]; // maximum of 12 consecutive registers to write
   uint8_t i;

   // init filters and mask data
   for(i = 0; i < 12; ++i)
   {
      data[i] = 0;
   }

   // set buffers to receive all messages
   write_register_mcp2515(chip, RXB0CTRL, (1<<RXM1) | (1<<RXM0));
   write_register_mcp2515(chip, RXB1CTRL, (1<<RXM1) | (1<<RXM0));

   // remove all bits from reception filter masks to receive all messages
   // mask 0/1
   write_multi_registers_mcp2515(chip,
                                 RXM1EID0 - RXM0SIDH + 1,
                                 RXM0SIDH,
                                 data);

   // filters 0/1/2
   write_multi_registers_mcp2515(chip,
                                 RXF2EID0 - RXF0SIDH + 1,
                                 RXF0SIDH,
                                 data);

   // filters 3/4/5
   write_multi_registers_mcp2515(chip,
                                 RXF5EID0 - RXF3SIDH + 1,
                                 RXF3SIDH,
                                 data);
}

/**
 * @brief set filters during configuration (static filters)
 * @param chip   - select chip to use
 * @param filter - pointer to filter struct
 *
 * \todo add filter setup implementation
 */
void setFilters(eChipSelect   chip,
                uint8_t*      filter)
{
   // nothing yet
}

