/*
  pins_arduino.h - Pin definition functions for Arduino
  Part of Arduino - http://www.arduino.cc/

  Copyright (c) 2007 David A. Mellis
  Copyright (c) 2015~2020 Spence Konde

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General
  Public License along with this library; if not, write to the
  Free Software Foundation, Inc., 59 Temple Place, Suite 330,
  Boston, MA  02111-1307  USA

  $Id: wiring.h 249 2007-02-03 16:52:51Z mellis $
*/

#ifndef Pins_Arduino_h
#define Pins_Arduino_h

#define ATTINYX4 1
#define __AVR_ATtinyX4__
#define USE_SOFTWARE_SPI 1

#include <avr/pgmspace.h>

#define NUM_DIGITAL_PINS            12
#define NUM_ANALOG_INPUTS           8
#define analogInputToDigitalPin(p)  ((p < 8) ? 10 -(p): -1)

#define ADC_TEMPERATURE 34

#define digitalPinHasPWM(p)         ((p) == 2 || (p) == 3 || (p) == 4 || (p) == 5)

//This part has a USI, not an SPI module. Accordingly, there is no MISO/MOSI in hardware. There's a DI and a DO. When the chip is used as master, DI is used as MISO, DO is MOSI; the defines here specify the pins for master mode, as SPI master is much more commonly used in Arduino-land than SPI slave, and these defines are required for compatibility. Be aware of this when using the USI SPI fucntionality (and also, be aware that the MISO and MOSI markings on the pinout diagram in the datasheet are for ISP programming, where the chip is a slave. The pinout diagram included with this core attempts to clarify this)


#define SS   7
#define MOSI 5
#define MISO 4
#define SCK  6

#define USI_DDR_PORT DDRA
#define USI_SCK_PORT DDRA
#define USCK_DD_PIN DDA4
#define DO_DD_PIN DDA5
#define DI_DD_PIN DDA6
#  define DDR_USI DDRA
#  define PORT_USI PORTA
#  define PIN_USI PINA
#  define PORT_USI_SDA PORTA6
#  define PORT_USI_SCL PORTA4
#  define PIN_USI_SDA PINA6
#  define PIN_USI_SCL PINA4
#  define USI_START_VECTOR USI_START_vect
#  define USI_OVERFLOW_VECTOR USI_OVF_vect
#  define DDR_USI_CL DDR_USI
#  define PORT_USI_CL PORT_USI
#  define PIN_USI_CL PIN_USI
#ifndef USI_START_COND_INT
#  define USI_START_COND_INT USISIF
#endif


static const uint8_t SDA = 4;
static const uint8_t SCL = 6;

//Ax constants cannot be used for digitalRead/digitalWrite/analogWrite functions, only analogRead().
static const uint8_t A0 = 0x80 | 0;
static const uint8_t A1 = 0x80 | 1;
static const uint8_t A2 = 0x80 | 2;
static const uint8_t A3 = 0x80 | 3;
static const uint8_t A4 = 0x80 | 4;
static const uint8_t A5 = 0x80 | 5;
static const uint8_t A6 = 0x80 | 6;
static const uint8_t A7 = 0x80 | 7;


#define PIN_PA0  (10)
#define PIN_PA1  ( 9)
#define PIN_PA2  ( 8)
#define PIN_PA3  ( 7)
#define PIN_PA4  ( 6)
#define PIN_PA5  ( 5)
#define PIN_PA6  ( 4)
#define PIN_PA7  ( 3)
#define PIN_PB0  ( 0)
#define PIN_PB1  ( 1)
#define PIN_PB2  ( 2)
#define PIN_PB3  (11)  /* RESET */
#define LED_BUILTIN (2)

//legacy
#define PIN_A0  (10)
#define PIN_A1  ( 9)
#define PIN_A2  ( 8)
#define PIN_A3  ( 7)
#define PIN_A4  ( 6)
#define PIN_A5  ( 5)
#define PIN_A6  ( 4)
#define PIN_A7  ( 3)
#define PIN_B0  ( 0)
#define PIN_B1  ( 1)
#define PIN_B2  ( 2)
#define PIN_B3  (11)  /* RESET */
#define LED_BUILTIN (2)

//----------------------------------------------------------
//----------------------------------------------------------
//Core Configuration (used to be in core_build_options.h)



//Choosing not to initialise saves power and flash. 1 = initialise.
#define INITIALIZE_ANALOG_TO_DIGITAL_CONVERTER    1
#define INITIALIZE_SECONDARY_TIMERS               1
/*
  The old standby ... millis on Timer 0.
*/
#define TIMER_TO_USE_FOR_MILLIS                   0

/*
  Where to put the software serial? (Arduino Digital pin numbers)
*/
//WARNING, if using software, TX is on AIN0, RX is on AIN1. Comparator is favoured to use its interrupt for the RX pin.
#define USE_SOFTWARE_SERIAL           1
//Please define the port on which the analog comparator is found.
#define ANALOG_COMP_DDR               DDRA
#define ANALOG_COMP_PORT              PORTA
#define ANALOG_COMP_PIN               PINA
#define ANALOG_COMP_AIN0_BIT          1
#define ANALOG_COMP_AIN1_BIT          2


/*
  Analog reference bit masks.
*/
// VCC used as analog reference, disconnected from PA0 (AREF)
#define DEFAULT (0)
// External voltage reference at PA0 (AREF) pin, internal reference turned off
#define EXTERNAL (1)
// Internal 1.1V voltage reference
#define INTERNAL (2)
#define INTERNAL1V1 INTERNAL

//----------------------------------------------------------
//----------------------------------------------------------
//----------------------------------------------------------
//----------------------------------------------------------



#define digitalPinToPCICR(p)    (((p) >= 0 && (p) <= 11) ? (&GIMSK) : ((uint8_t *)NULL))
#define digitalPinToPCICRbit(p) (((p) >= 3 && (p) <= 10) ? 4 : 5)
#define digitalPinToPCMSK(p)    (((p) >= 3 && (p) <= 10) ? (&PCMSK0) : ((((p) >= 0 && (p) <= 2) || ((p) == 11)) ? (&PCMSK1) : ((uint8_t *)NULL)))
#define digitalPinToPCMSKbit(p) (((p) >= 3 && (p) <= 10) ? (10 - (p)) : (((p) == 11) ? 3 : (p)))

#define digitalPinToInterrupt(p)  ((p) == 2 ? 0 : NOT_AN_INTERRUPT)
#ifdef ARDUINO_MAIN
// ATMEL ATTINY828
//
//             16*   26   24   14
//          17    27   25   15
//             PC0  PD2  PD0  PB6
//          PC1  PD3  PD1   PB7
//             _________________
// 18 RX  PC2 | *               | PB5   13
// 19 TX  PC3 |                 | PB4   12
// 20 *   PC4 |                 | PB3   11
//        VCC |                 | GND
//        GND |                 | PB2   10
// 21 *   PC5 |                 | PB1    9
// 22 *   PC6 |                 | AVCC
// 23     PC7 |_________________| PB0    8
//           PA0  PA2  PA4  PA6
//              PA1  PA3  PA5  PA7
//            0     2    4    6
//               1     3    5    7

// these arrays map port names (e.g. port B) to the
// appropriate addresses for various functions (e.g. reading
// and writing)
const uint8_t PROGMEM port_to_mode_PGM[] =
{
  NOT_A_PORT,
  (uint8_t)(uint16_t)&DDRA,
  (uint8_t)(uint16_t)&DDRB,
  (uint8_t)(uint16_t)&DDRC,
  (uint8_t)(uint16_t)&DDRD
};

const uint8_t PROGMEM port_to_output_PGM[] =
{
  NOT_A_PORT,
  (uint8_t)(uint16_t)&PORTA,
  (uint8_t)(uint16_t)&PORTB,
  (uint8_t)(uint16_t)&PORTC,
  (uint8_t)(uint16_t)&PORTD
};

const uint8_t PROGMEM port_to_pullup_PGM[] =
{
  NOT_A_PORT,
  (uint8_t)(uint16_t)&PUEA,
  (uint8_t)(uint16_t)&PUEB,
  (uint8_t)(uint16_t)&PUEC,
  (uint8_t)(uint16_t)&PUED
};

const uint8_t PROGMEM port_to_input_PGM[] =
{
  NOT_A_PORT,
  (uint8_t)(uint16_t)&PINA,
  (uint8_t)(uint16_t)&PINB,
  (uint8_t)(uint16_t)&PINC,
  (uint8_t)(uint16_t)&PIND
};

const uint8_t PROGMEM digital_pin_to_port_PGM[] =
{
  PORT_A_ID,
  PORT_A_ID,
  PORT_A_ID,
  PORT_A_ID,
  PORT_A_ID,
  PORT_A_ID,
  PORT_A_ID,
  PORT_A_ID,
  PORT_B_ID,
  PORT_B_ID,
  PORT_B_ID,
  PORT_B_ID,
  PORT_B_ID,
  PORT_B_ID,
  PORT_B_ID,
  PORT_B_ID,
  PORT_C_ID,
  PORT_C_ID,
  PORT_C_ID,
  PORT_C_ID,
  PORT_C_ID,
  PORT_C_ID,
  PORT_C_ID,
  PORT_C_ID,
  PORT_D_ID,
  PORT_D_ID,
  PORT_D_ID,
  PORT_D_ID
};

const uint8_t PROGMEM digital_pin_to_bit_mask_PGM[] =
{
  _BV(0),
  _BV(1),
  _BV(2),
  _BV(3),
  _BV(4),
  _BV(5),
  _BV(6),
  _BV(7),
  _BV(0),
  _BV(1),
  _BV(2),
  _BV(3),
  _BV(4),
  _BV(5),
  _BV(6),
  _BV(7),
  _BV(0),
  _BV(1),
  _BV(2),
  _BV(3),
  _BV(4),
  _BV(5),
  _BV(6),
  _BV(7),
  _BV(0),
  _BV(1),
  _BV(2),
  _BV(3),
};

const uint8_t PROGMEM digital_pin_to_timer_PGM[] =
{
  NOT_ON_TIMER,
  NOT_ON_TIMER,
  NOT_ON_TIMER,
  NOT_ON_TIMER,
  NOT_ON_TIMER,
  NOT_ON_TIMER,
  NOT_ON_TIMER,
  NOT_ON_TIMER,
  NOT_ON_TIMER,
  NOT_ON_TIMER,
  NOT_ON_TIMER,
  NOT_ON_TIMER,
  NOT_ON_TIMER,
  NOT_ON_TIMER,
  NOT_ON_TIMER,
  NOT_ON_TIMER,
  TIMER0A,
  NOT_ON_TIMER,
  NOT_ON_TIMER,
  NOT_ON_TIMER,
  TIMER0B,
  TIMER1A,
  TIMER1B,
  NOT_ON_TIMER,
  NOT_ON_TIMER,
  NOT_ON_TIMER,
  NOT_ON_TIMER
};



#endif

#endif

#endif