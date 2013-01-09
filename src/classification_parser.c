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

#include "classification_parser.h"

void classification_rule_error(const char * msg, char * rule)
{
	printf("Classification Rule Error: %s \"%s\"\n",msg,rule);
	exit(0);
}

void process_classification_rules(char * arg)
{
	/*avoid const chars.  :p*/
	char rules[strlen(arg)+1];
	strcpy(rules,arg);

	/*reentry points for tokenizing in nested loops*/
	char * save_semicolon, * save_colon, * save_comma;

	char * by_semicolon/*rule*/, 
	     * by_colon/*conversation number*/, 
	     * by_comma/*seq-number*/,
	     * by_equal;/*separate seq numbers from label*/
	
	char * label;
	unsigned int conversation_number,
		     seq,
		     seq_high = 0;

	struct classification * new_member;

	by_semicolon = strtok_r(rules,";",&save_semicolon);
	while(by_semicolon)
	{
		/*separate out the conversation numbers....*/
		by_colon = strtok_r(by_semicolon,":",&save_colon);
		if(by_colon != NULL)
		{
			conversation_number = atoi(by_colon);
			
			by_colon = strtok_r(NULL,":",&save_colon);
			if(by_colon != NULL)
			{
				/*separate out the label from the sequence numbers*/
				char * tmp;
				if((tmp = (strstr(by_colon,"="))) != NULL)
				{
					label = (char *)malloc(sizeof(char)*strlen(tmp));
					memcpy(label,(char *)tmp+1,sizeof(char)*strlen(tmp)); 

					if((by_equal = strtok(by_colon,"=")) != NULL)
					{
						/*Now we'll start building nodes with seq,seq_high*/
						if(!strstr(by_equal,","))
						{
							/*allocate space for a new conversation_rule*/
							new_member = malloc(sizeof(struct classification));
							new_member->root = malloc(sizeof(struct classification_tree_node));

							/*for just one value, we're done*/
							if(strstr(by_equal,"-"))
							{
								seq = atoi(strtok(by_equal,"-"));
								seq_high = atoi(strtok(NULL,"-"));
							}
							else
							{
								seq = atoi(by_equal);
								seq_high = 0;
							}
							
							new_member->conversation_number = conversation_number;
							new_member->root->label = label;
							new_member->root->seq = seq;
							new_member->root->seq_high = seq_high;

							add_classification(new_member);

						}
						else
						{
							by_comma = strtok_r(by_equal,",",&save_comma);
							while(by_comma)
							{	
								new_member = malloc(sizeof(struct classification));
								new_member->root = malloc(sizeof(struct classification_tree_node));
														
                                                        	if(strstr(by_comma,"-"))
                                                        	{
                                                                	seq = atoi(strtok(by_comma,"-"));
                                                                	seq_high = atoi(strtok(NULL,"-"));
                                                        	}
								else
								{
									seq = atoi(by_comma);
									seq_high = 0;
								}
							
								new_member->conversation_number = 
											conversation_number;
                                                        	new_member->root->label = label;
                                                      	 	new_member->root->seq = seq;
                                                        	new_member->root->seq_high = seq_high;

                                                        add_classification(new_member);	
								by_comma = strtok_r(NULL,",",&save_comma);
							}
						}	
					}
					else
					{
						classification_rule_error("Problem separating sequence numbers from label.",by_semicolon);
					}

				}
				else
				{
					classification_rule_error("Malformed, or no, label.",by_semicolon);
				}
			}
			else
			{
				classification_rule_error("Bad Sequence Number.",by_semicolon);
			}
		}
		else
		{
                	classification_rule_error("Malfored rule.",by_semicolon);
		}
		
		by_semicolon = strtok_r(NULL,";",&save_semicolon);
	}
}
