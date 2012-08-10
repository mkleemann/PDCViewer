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
 * \file PDCViewer.c
 *
 * \date Created: 09.08.2012 18:22:46
 * \author Matthias Kleemann
 **/


#include <stdbool.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/cpufunc.h>
#include <util/delay.h>

#include "util/util.h"
#include "spi/spi.h"
#include "can/can_mcp2515.h"
#include "timer/timer.h"
#include "PDCViewer.h"

// === GLOBALS ===============================================================


/**
 * \brief current state of FSM
 *
 * The state of the FSM is set and read from here.
 */
static volatile state_t fsmState     = INIT;


// === MAIN LOOP =============================================================

/**
 * \brief main loop
 *
 * The main loop consists of the FSM and calls all necessary init sequences
 * before entering it. Any error in the init process will result in
 * entering the error state.
 **/
int main(void)
{

   while (1)
   {
      switch (fsmState)
      {
         case RUNNING:
         {
            run();
            break;
         }

         case WAKEUP:
         {
            wakeUp();
            fsmState = RUNNING;
            break;
         }

         case SLEEP_DETECTED:
         {
            sleepDetected();
            fsmState = SLEEPING;
            break;
         }

         case SLEEPING:
         {
            sleeping();
            // set state WAKEUP here, too avoid race conditions
            // with pending interrupt
            fsmState = WAKEUP;
            break;
         }

         default:
         {
            errorState();
            fsmState = ERROR;
            break;
         }
      }
   }

   errorState();
}


// === FSM ===================================================================

/**
 * \brief Go to sleep mode. Deactivate CAN and set the sleep mode.
 *
 * Sleep trigger was detected (no CAN activity on master bus). All timers are
 * stopped. CAN controllers are put to sleep and AVR is  preparing for sleep
 * mode.
 */
void sleepDetected(void)
{
   // stop timer for now
   stopTimer1();
   stopTimer2();

   // set CAN controller to sleep
   mcp2515_sleep(CAN_CHIP1, INT_SLEEP_WAKEUP_BY_CAN);
}

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
void sleeping(void)
{
   cli();

   // enable wakeup interrupt INT0
   GICR  |= EXTERNAL_INT0_ENABLE;

   // let's sleep...
   set_sleep_mode(SLEEP_MODE_PWR_DOWN);
   // sleep_mode() has a possible race condition in it, so splitting it
   sleep_enable();
   sei();
   sleep_cpu();
   sleep_disable();

   // just in case...
   _NOP();
   _NOP();
   _NOP();

   // disable interrupt: precaution, if signal lies too long on pin
   GICR  &= ~(EXTERNAL_INT0_ENABLE);
}

/**
 * \brief wake up CAN and reinitialize the timers
 *
 * Now the AVR has woken up. Timers needs to be restarted and the CAN
 * controllers will also need to enter their working mode.
 */
void wakeUp(void)
{
   cli();

   // wakeup CAN bus
   mcp2515_wakeup(CAN_CHIP1, INT_SLEEP_WAKEUP_BY_CAN);

   // restart timers
   restartTimer1();
   restartTimer2();

   sei();
}

/**
 * \brief do all the work.
 *
 * \todo fetch information from CAN1
 */
void run(void)
{
   can_t msg;

   if (can_check_message_received(CAN_CHIP1))
   {
      // try to read message
      if (can_get_message(CAN_CHIP1, &msg))
      {
         // reset timer counter, since there is activity on master CAN bus
         setTimer1Count(0);

         // fetch information from CAN1
      }
   }
}

/**
 * \brief Error state
 *
 * Call this when an illegal state is reached. Only some status LEDs will
 * blink to show the error, but the system stops to work.
 */
void errorState(void)
{
}


// === ISR ===================================================================

/**
 * \brief interrupt service routine for Timer1 capture
 *
 * Timer1 input capture interrupt (~15s 4MHz@1024 prescale factor)
 **/
ISR(TIMER1_CAPT_vect)
{
   fsmState = SLEEP_DETECTED;
}

/**
 * \brief interrupt service routine for Timer2 compare
 *
 * Timer2 compare match interrupt handler
 **/
ISR(TIMER2_COMP_vect)
{
}

/**
 * \brief interrupt service routine for external interrupt 0
 *
 * External Interrupt0 handler to wake up from CAN activity
 **/
ISR(INT0_vect)
{
}

