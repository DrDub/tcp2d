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


#ifndef _CONVERSATION_LIST_
#define _CONVERSATION_LIST_

#include "conversation.h"
#include "conversation_print.h"
#include "string.h"

/*maps srcip-srcport-dstip-dstport combos to conversation lists*/
struct conversation_list
{
	/*identifiers for identifying unique streams*/
	char * src;
	char * dst;
	unsigned short src_port;
	unsigned short dst_port;
	
	/*the head of a matching conversation list*/
	struct conversation * head;

	struct conversation_list * next;
};

//Global where all of our conversations are dumped
extern struct conversation_list * tcp_conversations;

//For checking to see if conversation threads already exist
_Bool conversation_list_comparator(struct conversation_list *,struct conversation *);

//Allocate a new conversation list and give it the appropriate starting values
struct conversation_list * prepare_new_conversation_list(struct conversation *);

//Handles sorting conversations into their appropriate list
void add_conversation_list(struct conversation *);

//Passes the conversation to print_conversation (see conversation.h) for each list entry
void print_conversation_list(struct conversation_list *);

#endif
