/**
 *
 *  Copyright (C) <31,May,2023>  <Antony Lian>

 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.

 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.

 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.

**/

#ifndef HASHTABLE_HASHFUNC_H
#define HASHTABLE_HASHFUNC_H

#include "string.h"

#define MAX_STR_LEN 1024

#define hash_int int

//typedef size_t hash_int;

static hash_int hash_func(const char *name){
    char result[MAX_STR_LEN];
    hash_int hash_num = 0;
    strcpy(result,name);
    hash_int nameLen = (hash_int)strlen(result);
    if (nameLen >= 5){
        for (hash_int i = nameLen-1; i > nameLen-5; --i) {
            hash_num += (hash_int)(result[i]);
        }
    } else {
        for (int i = 0; i < nameLen; ++i) {
            hash_num += (hash_int)(result[i]);
        }
    }
    hash_num %= 10;
    return hash_num;
}




#endif //HASHTABLE_HASHFUNC_H
