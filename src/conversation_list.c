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


#include "conversation_list.h"

struct conversation_list * tcp_conversations = 0;

_Bool conversation_list_comparator(struct conversation_list * tcp_conversations,struct conversation * newmember)
{
	/*this ugly condition tests for both ip-port combos*/
	if((tcp_conversations->dst_port == newmember->dst_port || tcp_conversations->src_port == newmember->dst_port)
	&& (tcp_conversations->src_port == newmember->src_port || tcp_conversations->dst_port == newmember->src_port)
	&& (strcmp(tcp_conversations->dst,newmember->dst) || strcmp(tcp_conversations->src,newmember->dst))
	&& (strcmp(tcp_conversations->src,newmember->src) || strcmp(tcp_conversations->dst,newmember->src)))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/*a wild conversation_list node appears....*/
struct conversation_list * prepare_new_conversation_list(struct conversation * newmember)
{
	struct conversation_list * new_conversation =
                        (struct conversation_list *)malloc(sizeof(struct conversation_list));
        new_conversation->src_port = newmember->src_port;
        new_conversation->dst_port = newmember->dst_port;
        new_conversation->src = newmember->src;
        new_conversation->dst = newmember->dst;
        new_conversation->head = add_conversation(newmember,new_conversation->head);

	return new_conversation;
}

void add_conversation_list(struct conversation * newmember)
{
	struct conversation_list * current;
	struct conversation_list * placeholder;
	
	_Bool match_found = 0;

	/*if our global conversation list 'tcp_conversations' already has members do this....*/
	if(tcp_conversations)
	{
		/*this looping just finds the correct bin for our conversation*/
		if(conversation_list_comparator(tcp_conversations,newmember))
		{
			tcp_conversations->head = add_conversation(newmember,tcp_conversations->head);
		}
		else
		{	
			current = tcp_conversations->next;
			while(current)
			{
				if(conversation_list_comparator(current,newmember))
				{
					current->head = add_conversation(newmember,current->head);
					match_found = 1;
					break;
				}
				current = current->next;
			}
			/*or if there aren't matches, creates a new bin altogether*/
			if(!match_found)
			{
				placeholder = prepare_new_conversation_list(newmember);
				placeholder->next = tcp_conversations;
				tcp_conversations = placeholder;
			}
		}	
	}
	else/*tcp_conversations gets its first member!*/
	{
		tcp_conversations = prepare_new_conversation_list(newmember);
	}
}

void print_conversation_list(struct conversation_list * tcp_conversations)
{
	if(tcp_conversations)
	{
		//So we can change _outfile_ from its original state on each loop
		char * _out_;
		int count = 1;
		
		/*if we aren't splitting this part's easy....*/
		if(!argopts._split_output_)
		{
			_out_ = argopts._outfile_;
		}	
		/*otherwise we have to splice the conversation count with the filename*/
		if(argopts._split_output_ && argopts._outfile_)
		{
			_out_ = (char *)malloc(sizeof(char)*(2048+strlen(argopts._outfile_)));
			memset(_out_,0,sizeof(char)*strlen(_out_));
			sprintf(_out_,"%s.%i",_out_,count);
		}

		/*loop through the nodes and print all of conversations stored in them*/

		print_conversation(tcp_conversations->head,argopts._outfile_,count);
		
		struct conversation_list * current;
		current = tcp_conversations->next;
		while(current)
		{
			++count;
			if(argopts._split_output_ && argopts._outfile_)
        	        {
				memset(_out_,0,strlen(_out_)*sizeof(char));
				sprintf(_out_,"%s.%i",argopts._outfile_,count);
                	}
	
			print_conversation(current->head,_out_,count);
			current = current->next;
		}

        	//reset the outfile settings
	        if(argopts._outfile_)
        	{
                	argopts._outfile_ = 0;
	        }
        	if(argopts._split_output_)
	        {
        	        free(_out_);
	        }
		
	}
}	

