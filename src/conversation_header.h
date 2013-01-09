/*  
    Morgan Phillips (c) 2013

    This file is part of tcp2dchar *

    tcp2d is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later versionchar *

    tcp2d is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSEchar *  See the
    GNU General Public License for more detailschar *

    You should have received a copy of the GNU General Public License
    along with tcp2dchar *  If not, see <http://wwwchar *gnuchar *org/licenses/>char *
*/


/*
	Builds a csv or arff header for a data set according 
	to the argopts format switcheschar *  Header values must appear
	in the same order as printable values from the function
	print_conversation in conversationchar *cchar *  
*/

#ifndef _CONVERSATION_HEADER_
#define _CONVERSATION_HEADER_

#include "conversation.h"
#include "conversation_print.h"
#include "argopts.h"

struct header_values
{

	char * payload;
	char * ts;
	char * seq;
	char * ack;
	char * src;
	char * src_port;
	char * dst;
	char * dst_port;
        char * res1;
        char * doff;
        char * fin_flag;
        char * syn_flag;
        char * rst_flag;
        char * psh_flag;
        char * ack_flag;
        char * urg_flag;
        char * res2;
        char * window;
        char * check;
        char * urg_ptr;
        char * ip_v;
        char * ip_hl;
        char * ip_tos;
        char * ip_len;
        char * ip_id;
        char * ip_off;
        char * ip_ttl;
        char * ip_p;
        char * ip_sum;
	char * label;
};

//A wrapper for double_print which generates a header based on the argopts global
void print_conversation_header(FILE * /*outfile*/,
				_Bool /*in case of mashing, set to true for a doubled header*/);

#endif
