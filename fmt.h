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

/*@file fmt.h
* @author Ahmad Dajani <eng.adajani@gmail.com>
* @date 14 August 2021
* @brief FMT player header file
*/

#ifndef __FMT_H
    #define __FMT_H

    #define C_INSTRUMENT_HEADER "FMTInstruments"
    #define C_INSTRUMENT_VERSION "\1\0"
    #define C_MUSIC_HEADER "FMTracker"
    #define C_MUSIC_VERSION "\1\1"
    
    struct ChannelType {
        unsigned char name[8 + 1]; /* plus null */
        unsigned char sett[11];
    };

    unsigned char ***allocate_pattern(unsigned int patternNumber, unsigned int patternLength);
    unsigned int load_instruments(const char *fileName, struct ChannelType **instrument);
    unsigned int load_music(const char *fileName);
#endif
