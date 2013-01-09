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


#include "classification.h"

struct classification * classification_rules = 0;

_Bool classification_comparator(struct classification * first,struct classification * second)
{
	if(first->conversation_number > second->conversation_number)
	{
		return 1;
	}
	else
	{
		return 0;
	}	
}

void add_classification(struct classification * newmember)
{	
	struct classification * current, * last;
	
	_Bool match_found = 0;

	/*if our global conversation list 'tcp_conversations' already has members do this....*/
	if(classification_rules)
	{
		/*this looping just finds the correct bin for our conversation*/
		if(newmember->conversation_number == classification_rules->conversation_number)
		{
			//Add a new tree node
		}
		else
		{	
			current = classification_rules->next;
			while(current)
			{
				if(current->conversation_number == newmember->conversation_number)
				{
					//Add a new tree node
					match_found = 1;
					break;
				}
				current = current->next;
			}
			/*or if there aren't matches, creates a new bin altogether*/
			if(!match_found)
			{
 				if(!classification_rules->next)
                		{
                                	if(classification_comparator(classification_rules,newmember))
                                	{
                                        	newmember->next = classification_rules;
	        	                        classification_rules = newmember;
        	        	        }
		                        else
                	                {
                               		        classification_rules->next = newmember;
	                                }
		                }
		                else
                		{
		                        current = classification_rules->next;
                		        last = classification_rules;

		                        while(current->next)
                		        {
                                		last = current;
		                                current = current->next;
                		        }

	                                if(classification_comparator(current,newmember))
        	                        {
                	                        current->next = newmember;
                        	                last->next = newmember;
	                                }
        	                        else
                	                {
                        	                current->next = newmember;
                                	}

				}
			}	
		}
	}
	else
	{
		classification_rules = newmember;
	}
	
}

void add_classification_tree_node(struct classification_tree_node * newmember,
                                        struct classification_tree_node * root)
{
	
}

char * get_classification_label(struct conversation * current,int conversation_number)
{
	struct classification * placeholder;	

	/*jump to the correct node, and delete the ones that are already used*/
	while(classification_rules)
	{
		if(classification_rules->conversation_number >= conversation_number)
		{
			break;
		}
		else
		{
			placeholder = classification_rules;
			classification_rules = classification_rules->next;
			free(placeholder->root);
			free(placeholder);
		}
	}
	
	if(classification_rules)
	{
		if(classification_rules->conversation_number == conversation_number)
		{
			return classification_rules->root->label;
		}
		else
		{
			return argopts._default_label_;
		}
	}
	else
	{
		return argopts._default_label_;	
	}
}
