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


#ifndef _CONVERSATION_PRINT_
#define _CONVERSATION_PRINT_

#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

#include "classification.h"
#include "conversation.h"
#include "conversation_header.h"
#include "argopts.h"

typedef struct conversation conversation;

//Print to file & stdout with a conditional
void double_print(_Bool,/*send as true for the first argument in a series*/
                        _Bool,  /*conditional/only prints if this is set to true*/
                        FILE *, /*file to write to*/
                        const char *,.../*regular printf arguments*/
                        );
//Print a single node from conversation
void print_conversation_node(FILE * /*A potential outfile to pass to double_print*/,
			int /*number of packets printed so far*/,
			int /*current conversation number/count */,
			conversation * /*packet to print*/
			);

void print_conversation(conversation *,char * /*filename of outfile*/,
				int /*conversation count*/);

#endif
