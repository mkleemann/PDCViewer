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
 * \section util_sec_expansion Expansion of Macros
 * To ensure that you can enter one argument via a macro which then
 * brakes into two arguments
 *
 * \code
 * #define MyPinDef  D,2
 *
 * MyMacroUsingPinDefs(MyPindef);
 * \endcode
 *
 * the macro definitions have to provide such possibility to the
 * pre-processor.
 *
 * \code
 * #define MyMacroUsingPinDefs(x)      _MyMacroUsingPinDefs(x)
 * #define _MyMacroUsingPinDefs(x,y)   (x > y)
 * \endcode
 *
 * That's why some of the macro definitions are done the way they are.
 * Otherwise the preprocessor runs into trouble with the number of arguments.
 *
 * See _XYZ and EXP_XYZ macros for reference.
 *
 * - - -
 *
 * \file util.h
 *
 * \date Created: 04.12.2011 17:48:24
 * \author Matthias Kleemann
 *
 */



#ifndef UTIL_H_
#define UTIL_H_

#include <avr/io.h>

/**
 * @brief definition of pin operations
 *
 * Format of port or pin usage is x = port,pin.
 */
#define PIN(x)                   PIN ## x

/**
 * @brief definition of DDR (data direction register) operations
 *
 * Format of port or pin usage is x = port,pin.
 */
#define DDR(x)                   DDR ## x

/**
 * @brief definition of port operations
 *
 * Format of port or pin usage is x = port,pin.
 */
#define PORT(x)                  PORT ## x


//! sets given pin to input
#define PIN_SET_INPUT(x)         _PIN_SET_INPUT(x)
//! sets given pin to output
#define PIN_SET_OUTPUT(x)        _PIN_SET_OUTPUT(x)
//! sets given pin to input with active internal pullup resistor
#define PIN_SET_PULLUP(x)        _PIN_SET_INPUT(x); _SET_PIN(x)

//! set pin (to 1)
#define SET_PIN(x)               _SET_PIN(x)
//! reset pin (to 0)
#define RESET_PIN(x)             _RESET_PIN(x)
//! toggle pin (to 0->1 or 1->0)
#define TOGGLE_PIN(x)            _TOGGLE_PIN(x)

//! check if pin is set (to 1)
#define IS_SET(x)                _IS_SET(x)

// *************************************************************************
// NOTE: To get the arguments from definitions described above.
// *************************************************************************

//! get port from macro through expansion
#define GET_PORT(x)              _GET_PORT(x)
//! get pin from macro through expansion
#define GET_PIN(x)               _GET_PIN(x)

// *************************************************************************
// NOTE: Here the part to split the arguments to the real meaning behind.
// *************************************************************************

//! set pin to input - macro expansion
#define _PIN_SET_INPUT(x,y)      DDR(x) &= ~(1<<y)
//! set pin to output - macro expansion
#define _PIN_SET_OUTPUT(x,y)     DDR(x) |= (1<<y)

//! set pin (to 1) - macro expansion
#define _SET_PIN(x,y)            PORT(x) |= (1<<y)
//! reset pin (to 0) - macro expansion
#define _RESET_PIN(x,y)          PORT(x) &= ~(1<<y)
//! toggle pin state - macro expansion
#define _TOGGLE_PIN(x,y)         PORT(x) ^= (1<<y)

//! get port from port/pin macro defintion
#define _GET_PORT(x,y)           x
//! get pin from port/pin macro defintion
#define _GET_PIN(x,y)            y

//! almost same as BIT_IS_SET, but as bool with PORT, PIN settings
#define _IS_SET(x,y)              (0 != (PORT(x) & (1<<y)))

//! expand pin definition, if x is a macro definition
#define EXP_PIN(x)               PIN(x)
//! expand DDR definition, if x is a macro definition
#define EXP_DDR(x)               DDR(x)
//! expand port definition, if x is a macro definition
#define EXP_PORT(x)              PORT(x)

/**
 * \def BIT_IS_SET(value, bit)
 * @brief checks if bit in value is set - returns (1<<bit) if true
 */
#define BIT_IS_SET(value, bit)   (value & (1<<bit))
/**
 * \def BIT_IS_UNSET(value, bit)
 * @brief checks if bit in value is not set - returns (1<<bit) if true
 */
#define BIT_IS_UNSET(value, bit) (!(value & (1<<bit)))

//! access type for volatile uint8_t
typedef volatile uint8_t   vuint8_t;
//! access type for pointer of volatile uint8_t
typedef vuint8_t*          pvuint8_t;

// definition of debug printouts
#ifdef ___DEBUG_LEVEL___

   #include "../uart/uart.h"
//! initialize debug channel
   #define DEBUG_INIT()       uart_init()

//! defintion of debug print
   #define DEBUG_PRINT(s)     uart_puts(s)

#else  // ___DEBUG_LEVEL___

//! nothing to do...
   #define  DEBUG_PRINT(s)

#endif // not defined ___DEBUG_LEVEL___


#endif /* UTIL_H_ */