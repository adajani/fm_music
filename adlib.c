/***************************************************************************
* Copyright (C) 2021 by Ahmad Dajani                                       *
*                                                                          *
* This file is part of fm_music.                                           *
*                                                                          *
* fm_music is free software: you can redistribute it and/or modify it      *
* under the terms of the GNU Lesser General Public License as published    *
* by the Free Software Foundation, either version 3 of the License, or     *
* (at your option) any later version.                                      *
*                                                                          *
* fm_music is distributed in the hope that it will be useful,              *
* but WITHOUT ANY WARRANTY* without even the implied warranty of           *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            *
* GNU Lesser General Public License for more details.                      *
*                                                                          *
* You should have received a copy of the GNU Lesser General Public         *
* License along with fm_music.  If not, see <http://www.gnu.org/licenses/>.*
****************************************************************************/

/*@file adlib.c
* @author Ahmad Dajani <eng.adajani@gmail.com>
* @date 14 August 2021
* @brief adlib driver source file
* @see: https://bochs.sourceforge.io/techspec/adlib_sb.txt
*/

#include <dos.h> /* outportb, inportb, delay */
#include "adlib.h"

void fm_write_register(unsigned int reg, unsigned char data) {
    register unsigned int temp;

    outportb(FM_STATUS_PORT, reg);
    for(temp=0; temp<6; temp++) {
        (void)inportb(FM_STATUS_PORT);
    }

    outportb(FM_DATA_PORT, data);
    for(temp=0; temp<35; temp++) {
        (void)inportb(FM_STATUS_PORT);
    }
}

void fm_initialize(void) {
    register unsigned int address;
    for(address=1; address<=0xF5; address++) {
        fm_write_register(address, 0);
    }
}

unsigned int fm_detect(void) {
    register unsigned char data1, data2;

    /* 1) Reset both timers by writing 60h to register 4 */
    fm_write_register(FM_TIMER_CONTROL_FLAG, 0x60);
    /* 2) Enable the interrupts by writing 80h to register 4 */
    fm_write_register(FM_TIMER_CONTROL_FLAG, 0x80);
    /* 3) Read the status register (port 388h).  Store the result */
    data1 = inportb(FM_STATUS_PORT);
    /* 4) Write FFh to register 2 (Timer 1) */
    fm_write_register(FM_TIMER1_DATA_ADDRESS, 0xFF);
    /* 5) Start timer 1 by writing 21h to register 4 */
    fm_write_register(FM_TIMER_CONTROL_FLAG, 0x21);

    /* 6) Delay for at least 80 microseconds */
    delay(1); /* 1000 microseconds*/

    /* 7) Read the status register (port 388h).  Store the result */
    data2 = inportb(FM_STATUS_PORT);
    /* 8) Reset both timers by writing 60h to register 4 */
    fm_write_register(FM_TIMER_CONTROL_FLAG, 0x60);
    /* 9) Enable the interrupts by writing 80h to register 4 */
    fm_write_register(FM_TIMER_CONTROL_FLAG, 0x80);

    if((data1 & 0xE0) == 0 && (data2 & 0xE0) == 0xC0) {
        return SUCCESSFUL_RETURN;
    }
    return ERROR_ADLIB_NOT_FOUND;
}

