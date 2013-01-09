/*  
    Morgan Phillips (c) 2013

    This file is part of tcp2d.

    tcp2d is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    tcp2d is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with tcp2d.  If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef _ARGOPTS_FORMAT_
#define _ARGOPTS_FORMAT_

#include <stdio.h>
#include <string.h>

#include "argopts.h"

//changes the value of a boolean when a string match occurs
void quick_switch(char *, const char *,_Bool *,_Bool);

//set global optargs elements according to the format '-F' supplied
void process_format_string(char *);

#endif
