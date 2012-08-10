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
 * \file PDCViewer.h
 *
 * \date Created: 09.08.2012 22:23:25
 * \author Matthias Kleemann
 **/


#ifndef PDCVIEWER_H_
#define PDCVIEWER_H_

// === DEFINITIONS ===========================================================

/**
 * \brief INT0 trigger definition
 *
 * \code
 * ISC01 ISC00 Description
 *     0     0 The low level of INT0 generates an interrupt request
 *     0     1 Any logical change on INT0 generates an interrupt request
 *     1     0 The falling edge of INT0 generates an interrupt request
 *     1     1 The rising edge of INT0 generates an interrupt request
 * \endcode
 */
#define EXTERNAL_INT0_TRIGGER    0

/**
 * \brief setup for enabling the INT0 interrupt
 */
#define EXTERNAL_INT0_ENABLE     (1 << INT0)


// === TYPE DEFINITIONS ======================================================

/**
 * \brief defines all states of the FSM
 */
typedef enum
{
   //! initialize all hardware
   INIT           = 0,
   //! do all the work
   RUNNING        = 1,
   //! prepare sleep mode (AVR and CAN)
   SLEEP_DETECTED = 2,
   //! sleeping
   SLEEPING       = 3,
   //! wake up (AVR and CAN)
   WAKEUP         = 4,
   //! an error occurred, stop working
   ERROR          = 5
} state_t;


// === FSM ===================================================================

/**
 * \brief Go to sleep mode. Deactivate CAN and set the sleep mode.
 *
 * Sleep trigger was detected (no CAN activity on master bus). All timers are
 * stopped. CAN controllers are put to sleep and AVR is  preparing for sleep
 * mode.
 */
void sleepDetected(void);


/**
 * \brief enter AVR sleep mode
 *
 * AVR enters sleep mode and also wakes up in this state, so some intial
 * steps to set wakeup interrupt need to be done here.
 *
 * The three \c _NOP(); instructions are a safety, since older AVRs may
 * skip the next couple of instructions after sleep mode.
 *
 * Also a precaution is the disabling of the wake up interrupt, to avoid
 * several interrupts to happen, if the signal lies too long on the
 * external interrupt pin.
 */
void sleeping(void);

/**
 * \brief wake up CAN and reinitialize the timers
 *
 * Now the AVR has woken up. Timers needs to be restarted and the CAN
 * controllers will also need to enter their working mode.
 */
void wakeUp(void);

/**
 * \brief do all the work.
 */
void run(void);

/**
 * \brief Error state
 *
 * Call this when an illegal state is reached. Only some status LEDs will
 * blink to show the error, but the system stops to work.
 */
void errorState(void);


#endif /* PDCVIEWER_H_ */