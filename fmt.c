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

/*@file fmt.c
* @author Ahmad Dajani <eng.adajani@gmail.com>
* @date 14 August 2021
* @brief FMT player source file
* @see: https://bochs.sourceforge.io/techspec/FMT_sb.txt
*/

#include <stdio.h> /* FILE, fopen, fclose, fread */
#include <mem.h> /* memset */
#include <string.h> /* strcmp */
#include <assert.h> /* assert */
#include "fmt.h"

static unsigned char A_FMRegisters[] = {32, 64, 96, 128, 224, 192};
static int A_Delay[255] = {4};
static struct ChannelType channel[8] = {0};
static struct ChannelType *instrumentPtr = NULL;
static unsigned char ***pattern = NULL;

unsigned char ***allocate_pattern(unsigned int patternNumber, unsigned int patternLength) {
    register unsigned int y, x;
    unsigned char ***array;

    array = (unsigned char ***)malloc(patternNumber * sizeof(unsigned char**));
    assert(array != NULL);
    for(y=0; y<patternNumber; y++) {
        array[y] = (unsigned char **) malloc(patternLength * sizeof(unsigned char *));
        assert(array[y] != NULL);
        for(x=0; x<patternLength; x++) {
            array[y][x] = (unsigned char *)malloc(7 * sizeof(unsigned char));
            assert(array[y][x] != NULL);
        }
    }
    return array;
}

unsigned int load_instruments(const char *fileName, struct ChannelType **instrument) {
    char header[sizeof(C_INSTRUMENT_HEADER)];
    char version[sizeof(C_INSTRUMENT_VERSION)];
    char database_name[20 + 1]; /* plus null */
    char instrumentsCount = 0;
    register unsigned int index;
    FILE *file;

    file = fopen(fileName, "rb");
    if(!file) {
        return ERROR_FILE_NOT_FOUND;
    }

    memset(header, 0, sizeof(header));
    fread(&header, sizeof(header)-1, 1, file);
    if(strcmp(header, C_INSTRUMENT_HEADER) != 0) {
        return ERROR_INVALID_FILE;
    }

    memset(version, 0, sizeof(version));
    fread(&version, sizeof(version)-1, 1, file);
    if(strcmp(version, C_INSTRUMENT_VERSION) != 0) {
        return ERROR_INVALID_VERSION;
    }

    memset(database_name, 0, sizeof(database_name));
    fread(&database_name, sizeof(database_name)-1, 1, file);
    printf("Loading: %s\n", database_name);

    fread(&instrumentsCount, sizeof(instrumentsCount), 1, file);

    *instrument = (struct ChannelType *)malloc((instrumentsCount + 1) * sizeof(struct ChannelType));
    if(*instrument == NULL) {
        return ERROR_MEMORY_ALLOCATION;
    }
    memset(*instrument, NULL, (instrumentsCount + 1) * sizeof(struct ChannelType));

    for(index=0; index<=instrumentsCount; index++) {
       fread( (*instrument + index)->name, 8, 1, file);
    }

    for(index=0; index<=instrumentsCount; index++) {
       fread( (*instrument + index)->sett, 11, 1, file);
    }

    fclose(file);

    return SUCCESSFUL_RETURN;
}

unsigned int load_music(const char *fileName) {
    char header[sizeof(C_MUSIC_HEADER)];
    char version[sizeof(C_MUSIC_VERSION)];
    char traker_name[20 + 1];
    char song_name[32 + 1];
    register unsigned int index;
    FILE *file;

    file = fopen(fileName, "rb");
    if(!file) {
        return ERROR_FILE_NOT_FOUND;
    }

    memset(header, 0, sizeof(header));
    fread(&header, sizeof(header)-1, 1, file);
    if(strcmp(header, C_MUSIC_HEADER) != 0) {
        return ERROR_INVALID_FILE;
    }

    memset(version, 0, sizeof(version));
    fread(&version, sizeof(version)-1, 1, file);
    if(strcmp(version, C_MUSIC_VERSION) != 0) {
        return ERROR_INVALID_VERSION;
    }

    memset(traker_name, 0, sizeof(traker_name));
    fread(&traker_name, sizeof(traker_name)-1, 1, file);
    printf("Traker name: %s\n",traker_name);

    memset(song_name, 0, sizeof(song_name));
    fread(&song_name, sizeof(song_name)-1, 1, file);
    printf("Song name: %s\n",song_name);

    for(index=0; index<8; index++) {
        fread(channel[index].name, 8, 1, file);
        fread(channel[index].sett, 11, 1, file);
    }

    fclose(file);
    return SUCCESSFUL_RETURN;
}
