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
 * \file can_mcp2515.h
 *
 * \date Created: 28.11.2011 18:15:12
 * \author Matthias Kleemann
 **/



#ifndef CAN_MCP2515_H_
#define CAN_MCP2515_H_

#include <avr/io.h>
#include <stdbool.h>
#include <util/delay.h>

#include "../util/util.h"
#include "../spi/spi.h"
#include "can_defs_mcp2515.h"
#include "can_config_mcp2515.h"

/**************************************************************************/
/* TYPE DEFINITIONS                                                       */
/**************************************************************************/

/**
 * @brief index of internal CAN bitrate setup
 */
typedef enum
{
   //! 100kbps
   CAN_BITRATE_100_KBPS = 0,
   //! 125kbps
   CAN_BITRATE_125_KBPS = 1,
   //! maximum index of possible CAN bitrates
   NUM_OF_CAN_BITRATES  = 2         // always the last one!
} eCanBitRate;

/**
 * @brief MCP2515's waking up reasons from sleep mode
 */
typedef enum
{
   //! wakeup by CAN, do not put MCP2551 to sleep
   INT_SLEEP_WAKEUP_BY_CAN = 0,
   //! wakeup by AVR
   INT_SLEEP_MANUAL_WAKEUP = 1
} eInternalSleepMode;


/**
 * @brief CAN message format - no extended frame support yet
 */
typedef struct
{
   //! message id (11 bits)
   uint16_t    msgId;
   //! header of CAN message
   struct
   {
      //! remote transmit request frame
      unsigned int rtr : 1;
      //! data length
      unsigned int len : 4;
   } header;
   //! data bytes of CAN message
   uint8_t  data[8];
} can_t;


/**
 * @brief CAN filter format - no extended frame support yet
 */
typedef struct
{
   //! message id (11 bits)
   uint16_t id;
   //! message id mask to use as filter
   uint16_t mask;
   //! flags within message
   struct
   {
      //! remote transmit request frame
      unsigned int rtr : 2;
   } flags;
} can_filter_t;

/**
 * @brief CAN error states
 */
typedef enum
{
   //! Receive Buffer 1 Overflow
   CAN_ERR_RX1_OVERFLOW = 0,
   //! Receive Buffer 0 Overflow
   CAN_ERR_RX0_OVERFLOW = 1,
   //! Bus-Off Error when TEC reaches 255
   CAN_ERR_TX_BUS_OFF   = 2,
   //! Transmit Error-Passive when TEC is equal to or greater than 128
   CAN_ERR_TX_PASSIVE   = 3,
   //! Receive Error-Passive when REC is equal to or greater than 128
   CAN_ERR_RX_PASSIVE   = 4,
   //! Transmit Error Warning when TEC is equal to or greater than 96
   CAN_ERR_TX_WARNING   = 5,
   //! Receive Error Warning when REC is equal to or greater than 96
   CAN_ERR_RX_WARNING   = 6,
   //! Error Warning when TEC or REC is equal to or greater than 96
   CAN_ERR_WARNING      = 7,
   //! No Error detected
   CAN_ERR_NO_ERROR     = 8
} can_error_t;


/**************************************************************************/
/* MCP2515 REGISTER/INIT FUNCTIONS                                        */
/**************************************************************************/

/**
 * @brief  initializes MCP2515 selected
 *
 * \par Clock Speed
 * All MCP2515 connected to AVR need to have the same clock speed when
 * using the same bitrate! See array in can_init_mcp2515.c.
 *
 * \par SPI
 * MCP2515 init routine does NOT initializes SPI. This has to be done before.
 *
 * @param  chip      - select chip to use
 * @param  bitrate   - CAN bitrate of chip selected
 * @param  mode      - mode of operation of MCP2515 after init
 * @return true if ok, false if error
 */
bool can_init_mcp2515(eChipSelect chip,
                      eCanBitRate bitrate,
                      uint8_t mode);

/**
 * @brief  write to MCP2515 registers
 *
 * @param  chip      - select chip to use
 * @param  address   - register address of MCP2515
 * @param  data      - data byte
 */
void write_register_mcp2515(eChipSelect   chip,
                            uint8_t       address,
                            uint8_t       data);


/**
 * \brief  write sequential to MCP2515 registers
 *
 * \param  chip      - select chip to use
 * \param  length    - length of buffer
 * \param  address   - register address of MCP2515 (start)
 * \param  data      - data buffer
 */
void write_multi_registers_mcp2515(eChipSelect   chip,
                                   uint8_t       length,
                                   uint8_t       address,
                                   uint8_t*      data);

/**
 * @brief  read from MCP2515 registers
 *
 * @param  chip      - select chip to use
 * @param  address   - register address of MCP2515
 * @return data      - data byte
 */
uint8_t read_register_mcp2515(eChipSelect chip,
                              uint8_t     address);

/**
 * @brief  write masked bits to MCP2515 registers
 *
 * Note: Not all registers are able to provide this functionality. Mostly
 *       configuration registers do. Read the datasheet for details.
 *
 * @param  chip      - select chip to use
 * @param  address   - register address of MCP2515
 * @param  mask      - bit mask for modify
 * @param  data      - data byte
 */
void bit_modify_mcp2515(eChipSelect chip,
                        uint8_t     address,
                        uint8_t     mask,
                        uint8_t     data);


/**
 * @brief  reads MCP2515 status registers
 *
 * @param  chip    - select chip to use
 * @param  command - read quick status command of MCP2515
 * @return value of status register
 */
uint8_t read_status_mcp2515(eChipSelect  chip,
                            uint8_t      command);

/**
 * @brief  put MCP2515 (and attached MCP2551) to sleep
 *
 * To put MCP2551 also to sleep, connect RX1BF pin to RS pin of MCP2551. It
 * is not always wanted to wakeup on any CAN activity. Sometimes, with
 * multiple interfaces, the "master bus" should only trigger the wakeup,
 * whereas the "slave" interfaces are woken up by wakeup signal from
 * ATmega.
 *
 * @param  chip - chip to use
 * @param  mode - how/when to activate MCP2515 again
 */
void mcp2515_sleep(eChipSelect         chip,
                   eInternalSleepMode  mode);

/**
 * @brief  wakeup MCP2515 (and attached MCP2551) from sleep mode
 *
 * @param  chip - chip to use
 * @param  mode - how/when to activate MCP2515 again
 *
 * If in manual wakeup mode, a special sequence is needed to wake the
 * MCP2515 up. This is not needed, when activating the controller by CAN
 * bus activity.
 *
 * \note
 * The CAN controller starts in LISTEN ONLY mode after wakeup. The last mode
 * when fully operable will be set after wakeup.
 *
 * \attention
 * The MCP2515 will wake up when bus activity occurs or <b>when the MCU sets,
 * via the SPI interface, the CANINTF.WAKIF bit to 'generate' a wake-up
 * attempt (the CANINTE.WAKIE bit must also be set in order for the wake-up
 * interrupt to occur).</b>
 */
void mcp2515_wakeup(eChipSelect         chip,
                    eInternalSleepMode  mode);

/**
 * @brief  set MCP2515 mode of operation
 *
 * @param  chip - select chip to use
 * @param  mode - mode of operation of MCP2515
 */
void set_mode_mcp2515(eChipSelect   chip,
                      uint8_t       mode);

/**
 * @brief clear filters
 * @param chip - select chip to use
 */
void clear_filters(eChipSelect chip);

/**
 * @brief set filters during configuration (static filters)
 * @param chip   - select chip to use
 * @param filter - pointer to filter struct
 */
void setFilters(eChipSelect chip,
                uint8_t*    filter);

/************************************************************************/
/* CAN FUNCTIONS                                                        */
/************************************************************************/

/**
 * @brief  send message via CAN
 *
 * @param  chip - select chip to use
 * @param  msg  - pointer to CAN message to send
 * @return address of buffer used to send
 */
uint8_t can_send_message(eChipSelect chip,
                         can_t*      msg);

/**
 * @brief  get received CAN message
 *
 * @param  chip - select chip to use
 * @param  msg  - pointer to CAN message to send
 * @return filter match status + 1
 */
uint8_t can_get_message(eChipSelect chip,
                        can_t*      msg);

/**
 * @brief  checks if any messages are received (via MCP2515's interrupt pin)
 * @param  chip - select chip to use
 * @return true if message was received
 */
bool can_check_message_received(eChipSelect chip);

/**
 * @brief  checks if any tx buffer is free to be loaded with a message
 * @param  chip - select chip to use
 * @return true if a buffer is free
 */
bool can_check_free_tx_buffers(eChipSelect chip);

/**
 * @brief aborting all CAN transmissions
 * @param  chip - select chip to use
 */
void can_abort_all_transmissions(eChipSelect chip);

/**
 * @brief  get error state of CAN bus
 * @param  chip - select chip to use
 * @return error state
 */
can_error_t can_get_bus_errors(eChipSelect chip);

/**************************************************************************/
/* HELPERS                                                                */
/**************************************************************************/

/**
 * @brief setting up the interrupt pins
 * @param  chip - select chip to use
 */
void setup_interrupt_pins(eChipSelect chip);

/**
 * @brief setting up the chip select pins
 * @param  chip - select chip to use
 */
void setup_cs_pins(eChipSelect chip);

/**
 * @brief set chip select for the right chip
 * @param  chip - select chip to use
 */
void set_chip_select(eChipSelect chip);

/**
 * @brief unset chip select for the right chip
 * @param  chip - select chip to use
 */
void unset_chip_select(eChipSelect chip);


#endif /* CAN_MCP2515_H_ */
