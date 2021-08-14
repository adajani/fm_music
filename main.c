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

/*@file main.c
* @author Ahmad Dajani <eng.adajani@gmail.com>
* @date 14 August 2021
* @brief FMT tracker entry source file
*/
#include "adlib.h"
#include "fmt.h"
#include "panic.h"

int main(int argc, char **argv) {
    register unsigned int status;
    (void)argc;
    (void)argv;

    status = fm_detect();
    if(status != SUCCESSFUL_RETURN) {
        panic(status);
    }

    fm_initialize();

    status = load_instruments("inst\\default.fmi", &instrumentPtr);
    if(status != SUCCESSFUL_RETURN) {
        panic(status);
    }

    status = load_music("sample\\sample01.fmt");
    if(status != SUCCESSFUL_RETURN) {
        panic(status);
    }

    return SUCCESSFUL_RETURN;
}