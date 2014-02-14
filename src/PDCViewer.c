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


#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/cpufunc.h>

#include "leds/leds.h"
#include "can/can_mcp2515.h"
#include "timer/timer.h"
#include "matrixbar/matrixbar.h"
#include "PDCViewer.h"

// === GLOBALS ===============================================================

/**
 * \brief testing w/o CAN
 */
//#define ___NO_CAN___

/**
 * \brief current state of FSM
 *
 * The state of the FSM is set and read from here.
 */
state_t fsmState       = INIT;

/**
 * \brief set current column
 */
uint8_t columnInUse    = 0;

/**
 * \brief save input values to show
 * \note The struct isn't really necessary, but makes it easier to provide
 * simple add-ons.
 */
typedef struct
{
   //! array of PDC values to save
   uint8_t  sensorVal[NUM_OF_PDC_VALUES];
} storage_t;

/**
 * \brief storage of values in use
 */
storage_t storage;

// === MAIN LOOP =============================================================

/**
 * \brief main loop
 *
 * The main loop consists of the FSM and calls all necessary init sequences
 * before entering it. Any error in the init process will result in
 * entering the error state.
 *
 * \returns  nothing, since it does not return
 **/
#ifndef __DOXYGEN__
int __attribute__((OS_main)) main(void)
#else
int main(void)
#endif
{

   initHardware();

#ifndef ___NO_CAN___
   if(true == initCAN())
   {
#endif
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
#ifndef ___NO_CAN___
   }
#endif

   // something went wrong here
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
   // leds off to save power
   led_all_off();
   matrixbar_clear();

#ifndef ___NO_CAN___
   // set CAN controller to sleep
   mcp2515_sleep(CAN_CHIP1, INT_SLEEP_WAKEUP_BY_CAN);
#endif
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

#ifndef ___NO_CAN___
   // wakeup CAN bus
   mcp2515_wakeup(CAN_CHIP1, INT_SLEEP_WAKEUP_BY_CAN);
#endif

   // restart timers
   restartTimer1();
   restartTimer2();
   // set status LED to show run state
   led_on(statusLed);

   sei();
}

/**
 * \brief do all the work.
 *
 * \todo fetch information from CAN1
 */
void run(void)
{
#ifndef ___NO_CAN___
   can_t    msg;
   uint8_t  i, idx;

   if (can_check_message_received(CAN_CHIP1))
   {
      // try to read message
      if (can_get_message(CAN_CHIP1, &msg))
      {
         // reset timer counter, since there is activity on master CAN bus
         setTimer1Count(0);

         // fetch information from CAN
         if ((PDC_CAN_ID == msg.msgId) && (0 == msg.header.rtr))
         {
            // fetch only rear sensors
            for (i = 0; i < msg.header.len; ++i)
            {
               // bytes 2/3/6/7 match to 0..3 (num of matrix columns)
               // 0<-2 0000<-0010
               // 1<-3 0001<-0011
               // 2<-6 0010<-0110
               // 3<-7 0011<-0111
               // only, if bit 1 is set to fetch rear values
               if (i & 0x02)
               {
                  // index is bit 0 + (bit 2 >> 1)
                  idx = (i & 0x01) + ((i & 0x04) >> 1);
                  storage.sensorVal[idx] = msg.data[i];
               }
            }
         }
      }
   }
#else
   // testing w/o CAN

   // reset timer counter
   setTimer1Count(0);
#endif

   // set matrix bargraph
//   matrixbar_reset_col(++columnInUse);
//   matrixbar_set(storage.sensorVal[columnInUse % NUM_OF_PDC_VALUES]);
//   matrixbar_set_col(columnInUse);
}

/**
 * \brief Error state
 *
 * Call this when an illegal state is reached. Only some status LEDs will
 * blink to show the error, but the system stops to work.
 */
void errorState(void)
{
   led_toggle(statusLed);
   _delay_ms(500);
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
 * \brief interrupt service routine for Timer2 capture
 *
 * Timer2 input compare interrupt (~50ms 4MHz@1024 prescale factor)
 **/
ISR(TIMER2_COMP_vect)
{
   // set timeout flag
}

/**
 * \brief interrupt service routine for external interrupt 0
 *
 * External Interrupt0 handler to wake up from CAN activity
 **/
ISR(INT0_vect)
{
   // does not need to do anything, but needs to be there
}


// === HELPERS ===============================================================


/**
 * \brief Initialize Hardware
 *
 * Setting up the peripherals to the AVR and the wake-up interrupt
 * trigger.
 *
 * * \ref page_timers to trigger events
 *
 * * \ref page_spi to communicate to the MCP2515
 *
 * * \ref page_matrixbar to give user feedback
 *
 */
void initHardware(void)
{
   int i;

   // set timer for bussleep detection
   initTimer1(TimerCompare);
   // set timer for PDC off detection
   initTimer2(TimerCompare);

#ifndef ___NO_CAN___
   // initialize the hardware SPI with default values set in spi/spi_config.h
   spi_pin_init();
   spi_master_init();
#endif

   // set storage to initial values
   for(i = 0; i < NUM_OF_PDC_VALUES; ++i)
   {
      storage.sensorVal[i] = PDC_OUT_OF_RANGE;
   }

   // init matrix bargraph
   matrixbar_init();
   // init status LED and switch to on
   led_init();
   led_on(statusLed);

   // set wakeup interrupt trigger on low level
   MCUCR |= EXTERNAL_INT0_TRIGGER;

#ifdef ___NO_CAN___
   // It's not done in initCAN()!
   fsmState = RUNNING;
#endif
}

/**
 * \brief Initialize the CAN controllers
 *
 * Calls can_init_mcp2515 for each attached CAN controller and setting up
 * bit rate. If an error occurs some status LEDs will indicate it.
 *
 * See chapter \ref page_can_bus for further details.
 *
 * @return true if all is ok. Otherwise false is returned.
 */
bool initCAN(void)
{
   bool retVal = can_init_mcp2515(CAN_CHIP1, CAN_BITRATE_100_KBPS, LISTEN_ONLY_MODE);
   // If an error roccurs, the main loop is not started, so it's ok to set
   // the state here.
   fsmState = RUNNING;
   return retVal;
}

