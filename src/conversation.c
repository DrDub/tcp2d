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


#include "conversation.h"

_Bool ack_comparator(struct conversation * first,struct conversation * second)
{
	if((first->ack == second->seq))
	{	
		return 0;
	}
	else if((first->ack > second->ack))
	{
		return 1;
	}
	else
	{
		return 0;
	}	
}

_Bool duplicate_comparator(struct conversation * first,struct conversation * second)
{
	if((first->ack == second->ack) && (first->seq == second->seq))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

struct conversation * add_conversation(struct conversation * new_member,struct conversation * head)
{	
	struct conversation * current;
	struct conversation * last;
	
	if(!head)
	{
		head = new_member;
	}
	else
	{
		if(!head->next)
		{	
			if(!(duplicate_comparator(head,new_member) && argopts._drop_duplicates_))
			{
				if(ack_comparator(head,new_member))
				{
					new_member->next = head;
					head = new_member;
				}
				else
				{
					head->next = new_member;
				}
			}
		}
		else
		{
			current = head->next;
			last = head;
			
			while(current->next)
			{
				last = current;
				current = current->next;
			}
                       
			if(!(duplicate_comparator(current,new_member) && argopts._drop_duplicates_))
			{
				if(ack_comparator(current,new_member))
				{
					current->next = new_member;
                                	last->next = new_member;
				}
				else
				{ 
					current->next = new_member;
				}
			}

			return head;
		}

	}
}

