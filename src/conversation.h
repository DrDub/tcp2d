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


#ifndef _CONVERSATION_
#define _CONVERSATION_

#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

#include "argopts.h"
#include "conversation_print.h"

/*A combo of all ip/tcp fields from netinet/ip.h/tcp.h which aren't 
 part of the default output format.*/
struct extra_header_info
{

	/*TCP*/
	u_int16_t res1:4;
        u_int16_t doff:4;
        u_int16_t fin:2;
        u_int16_t syn:1;
        u_int16_t rst:1;
        u_int16_t psh:1;
        u_int16_t ack:1;
        u_int16_t urg:1;
        u_int16_t res2:2;

        u_int16_t window;
        u_int16_t check;
        u_int16_t urg_ptr;

	/*IP*/
	unsigned int ip_v;                
    	unsigned int ip_hl;              
    	u_int8_t ip_tos;                
    	u_short ip_len;                    
    	u_short ip_id;                      
    	u_short ip_off;                     
    	u_int8_t ip_ttl;                    
    	u_int8_t ip_p;                     
    	u_short ip_sum;                   


};

//Linked list node that holds tcp packets and classification data
struct conversation
{
	/*TCP header stuff*/
	unsigned long seq;
	unsigned long ack;

	unsigned short src_port;
	unsigned short dst_port;

	/*IP header stuff*/

	char * src;
	char * dst;
	
	/*Holds all non-default header info for IP and TCP*/	
	struct extra_header_info extra;
	
	/*Time*/
        unsigned long sec;
        unsigned long usec;
	
	char * payload;
	
	char * payload_buffer;

	struct conversation * next;
};

/*Links a conversation node to an existing list; tries to place all new members 
	in the proper flow order according to the seq-ack (see ack_comparator)
	and returns a new conversation head for inclusion in a conversation_list*/
struct conversation * add_conversation(struct conversation *,struct conversation *);

/*compare ack numbers (ascending order), returns true unless the 
 compared ack and seq values are equal (indicating a proper pairing).*/
_Bool ack_comparator(struct conversation *,struct conversation *);
/*compare seq->seq and ack->ack (see if packet should be dropped)*/
_Bool duplicate_comparator(struct conversation *,struct conversation *);

#endif
