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

/*@file adlib.h
* @author Ahmad Dajani <eng.adajani@gmail.com>
* @date 14 August 2021
* @brief adlib driver header file
* @see: https://bochs.sourceforge.io/techspec/adlib_sb.txt
*/

#ifndef __ADLIB__H
    #define __ADLIB__H

    enum E_FM_PORTS {
         FM_STATUS_PORT = 0x388 /* R/W */,
         FM_DATA_PORT  = 0x389 /* W/O */
    };

    enum E_FM_Registers {
         FM_TIMER1_DATA_ADDRESS = 2,
         FM_TIMER_CONTROL_FLAG = 4
    };

    void fm_write_register(unsigned int reg, unsigned char data);
    void fm_initialize(void);
    unsigned int fm_detect(void);
#endif