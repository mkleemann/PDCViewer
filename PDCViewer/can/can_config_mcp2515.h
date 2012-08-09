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
 * \file can_config_mcp2515.h
 *
 * Here you can add the configuration(s) you need. Some of them are not
 * to be changed without the need of adapting the code itself. Most likely
 * any type definitions you find here.
 *
 * \date Created: 28.11.2011 18:35:54
 * \author Matthias Kleemann
 **/



#ifndef CAN_CONFIG_MCP2515_H_
#define CAN_CONFIG_MCP2515_H_

/**************************************************************************/
/* TYPEDEFINITIONS                                                        */
/*                                                                        */
/* Note: Add here what you need to add, but keep the naming scheme the    */
/*       same. You may need to adapt the source - so be careful.          */
/**************************************************************************/

/**
 * @brief index of MCP2515 chips connected
 *
 * Any adaption here may need to adapt the source. If you keep the naming
 * scheme like CAN_CHIPx, it's easier because of macros using the definitions.
 */
typedef enum
{
   //! chip 1 (master CAN)
   CAN_CHIP1      = 0,
   //! chip 2 (slave CAN)
   CAN_CHIP2      = 1,
   //! always the last one!
   NUM_OF_MCP2515 = 2
} eChipSelect;


/**************************************************************************/
/* SETTINGS                                                               */
/**************************************************************************/

// Port definitions to access the two MCP2515

/**
 * \def CHIP1_CS_PIN
 * \brief chip select pin of CAN controller 1
 *
 * \def CHIP1_INT_PIN
 * \brief (receive) interrupt pin of CAN controller 1
 */
#define CHIP1_CS_PIN       B,2
#define CHIP1_INT_PIN      D,2

/**
 * \def CHIP2_CS_PIN
 * \brief chip select pin of CAN controller 2
 *
 * \def CHIP2_INT_PIN
 * \brief (receive) interrupt pin of CAN controller 2
 */
#define CHIP2_CS_PIN       B,1
#define CHIP2_INT_PIN      D,3

#endif /* CAN_CONFIG_MCP2515_H_ */