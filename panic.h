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

/*@file panic.h
* @author Ahmad Dajani <eng.adajani@gmail.com>
* @date 14 August 2021
* @brief Exception header file
*/

#ifndef __PANIC_H
    #define __PANIC_H

    #define ERROR_DESTINATION stdout

    enum E_ERROR {
        SUCCESSFUL_RETURN=0,
        ERROR_ADLIB_NOT_FOUND,
        ERROR_FILE_NOT_FOUND,
        ERROR_INVALID_FILE,
        ERROR_INVALID_VERSION,
        ERROR_MEMORY_ALLOCATION
    };

    void panic(enum E_ERROR error);
#endif