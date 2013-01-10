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

#ifndef _CLASSIFICATION_
#define _CLASSIFICATION_

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "conversation.h"

/*
like with the conversations, classification rules will be stored
in an ordered linked list.  However, each list node will contain a binary tree 
for sequence numbers.

classification labels are applied during the printing of a conversation (see conversation_print.h)

*/
struct classification
{
	int conversation_number;
	struct classification_tree_node * root;
	struct classification * next;
};

struct classification_tree_node
{
        /*
        if seq_high is greater than zero this defines a range
        [seq,seq_high]
        */
        unsigned int seq;
        unsigned int seq_high;

        char * label;

	struct classificatin_tree_node * left, * right;
};

//Global struct
extern struct classification * classification_rules;

//Orders by conversation number ascending
_Bool classification_comparator(struct classification *, struct classification *);

//Order and add to classification_rules
void add_classification(struct classification *);

//Grow a tree of sequence numbers in the classification node
void add_classification_tree_node(struct classification_tree_node * /*new member*/,
					struct classification_tree_node * /*root*/);

_Bool classification_tree_comparator(struct classification_tree_node *, 
                                                struct conversation * );

//Returns a label when conversation_number and sequence number match
char * get_classification_label(struct conversation * /*conversation to compare*/,int conversation_number);


#endif
