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


#include "conversation_print.h"

void double_print(_Bool reset_first_argument_condition,
			_Bool condition,FILE * out,const char * fmt, ...)
{
	/*prevents adding a delimitor to the beginning of the first entry*/
	static _Bool first_argument_condition = 1;

	if(reset_first_argument_condition)
	{
		first_argument_condition = 1;
	}

	if(condition)
	{

		va_list ap;
		if(!argopts._quiet_)
		{
			if(!first_argument_condition)
			{
				printf("%s",argopts._delimitor_);			
			}

			va_start(ap, fmt);
			vprintf(fmt, ap);
			va_end(ap);
		}
		if(out)
		{
			if(!first_argument_condition)
			{
				fprintf(out,"%s",argopts._delimitor_);
			}

			va_start(ap, fmt);
			vfprintf(out, fmt, ap);
			va_end(ap);
		}
		
		first_argument_condition = 0;
	}
}

void print_conversation_node(FILE * out,int packet_count,int conversation_count,struct conversation * head)
{
	_Bool first_local_run = 1;
			
	/*payload*/
        double_print(first_local_run,argopts._print_payload_,
           	out,"\"%s\"",head->payload);
	
	first_local_run = 0;
	
	/*timestamp*/
	double_print(first_local_run,argopts._print_timestamp_,
		out,"%u.%u",head->sec,head->usec);			

	/*seq number*/
	double_print(first_local_run,argopts._print_seq_,
		out,"%u",head->seq);
			
	/*ack number*/
	double_print(first_local_run,argopts._print_ack_,
		out,"%u",head->ack);
	
	/*src ip*/
	double_print(first_local_run,argopts._print_src_ip_,
		out,"%s",head->src);
	/*src port*/
	double_print(first_local_run,argopts._print_src_port_,
		out,"%u",head->src_port);
	/*dst ip*/
	double_print(first_local_run,argopts._print_dst_ip_,
		out,"%s",head->dst);
	/*dst port*/
	double_print(first_local_run,argopts._print_dst_port_,
		out,"%u",head->dst_port);

	/*extras*/

	double_print(first_local_run,argopts._print_res1_,
		out,"%u",head->extra.res1);
	double_print(first_local_run,argopts._print_doff_,
		out,"%u",head->extra.doff);

	/*tcpflags*/
	double_print(first_local_run,argopts._print_fin_flag_,
		out,"%u",head->extra.fin);
	double_print(first_local_run,argopts._print_syn_flag_,
		out,"%u",head->extra.syn);
	double_print(first_local_run,argopts._print_rst_flag_,
		out,"%u",head->extra.rst);
	double_print(first_local_run,argopts._print_psh_flag_,
		out,"%u",head->extra.psh);
	double_print(first_local_run,argopts._print_ack_flag_,
		out,"%u",head->extra.ack);
	double_print(first_local_run,argopts._print_urg_flag_,
		out,"%u",head->extra.urg);
	
	double_print(first_local_run,argopts._print_res2_,
		out,"%u",head->extra.res2);
	double_print(first_local_run,argopts._print_window_,
		out,"%u",head->extra.window);
	double_print(first_local_run,argopts._print_check_,
		out,"%u",head->extra.check);
	double_print(first_local_run,argopts._print_urg_ptr_,
		out,"%u",head->extra.urg_ptr);
	double_print(first_local_run,argopts._print_ip_v_,
		out,"%u",head->extra.ip_v);
	double_print(first_local_run,argopts._print_ip_hl_,
		out,"%u",head->extra.ip_hl);
	double_print(first_local_run,argopts._print_ip_tos_,
		out,"%u",head->extra.ip_tos);
	double_print(first_local_run,argopts._print_ip_len_,
		out,"%u",head->extra.ip_len);
	double_print(first_local_run,argopts._print_ip_id_,
		out,"%u",head->extra.ip_id);
	double_print(first_local_run,argopts._print_ip_off_,
		out,"%u",head->extra.ip_off);
	double_print(first_local_run,argopts._print_ip_ttl_,
		out,"%u",head->extra.ip_ttl);
	double_print(first_local_run,argopts._print_ip_p_,
		out,"%u",head->extra.ip_p);
	double_print(first_local_run,argopts._print_ip_sum_,
		out,"%u",head->extra.ip_sum);	

	/*See about printing a label from classification_rules*/
	if(argopts._classification_rules_)
	{
		double_print(first_local_run,1,
				out,"%s",get_classification_label(head,conversation_count));
	}

	if(!argopts._no_wrap_)
	{
		if(argopts._mash_)
		{
			if(packet_count%2 == 0)
			{
				double_print(1,1,out,"\n");
			}
		}
		else
		{
			double_print(1,1,out,"\n");
		}
	}

}

void print_conversation(struct conversation * head,char * output,int conversation_count)
{
	FILE * out = 0;
	/*use this instead of head to keep from losing our place*/
	struct conversation * placeholder = head;

	if(output)
	{
		if(!argopts._binary_dump_)
		{
			out = fopen(output,"a+");
		}
	}


      /* Used for ip comparison when _mash_ is enabled keeps 
                track of 'last' values to find matching pairs*/
        struct conversation * last = 0;

        int packet_count = 1;
        _Bool skip_current_packet = 0;

	/*so long as we're not just listing conversations....*/
	if(!argopts._list_conversations_)
	{
		if(argopts._header_ && !argopts._binary_dump_)
		{
			if(argopts._split_output_)
			{
				print_conversation_header(out,0);
				if(argopts._mash_)
				{
					double_print(0,1,out,"");
					print_conversation_header(out,1);
				}
			}
			else if(conversation_count < 2)
			{
				print_conversation_header(out,0);
				if(argopts._mash_)
				{
					double_print(0,1,out,"");
					print_conversation_header(out,1);
				}
			}
		}
		
		while(placeholder)
		{
			/*binary dump gets its own loop and overrides other input types*/
			if(output && argopts._binary_dump_)
			{
	
				if(placeholder->payload)
				{
                	        	char * bin_out = (char *)
                 		               malloc(sizeof(char)*strlen(output)+strlen(placeholder->src)+1);

                               	        strcat(bin_out,output);
                                        strcat(bin_out,".");
                                        strcat(bin_out,placeholder->src);

                                        out = fopen(bin_out,"a+");
						
					fwrite(placeholder->payload,sizeof(placeholder->payload),
						strlen(placeholder->payload),out);

					fclose(out);
				}

			}
			else/*if it's not a binary dump....*/
			{
				/*if the streams are being mashed alter the rules regarding newlines and delimitors*/
				if(last && argopts._mash_)
				{
					if(last->src_port != placeholder->src_port)
					{
						if(packet_count%2 == 0)
						{
							print_conversation_node(out,packet_count-1,conversation_count,last);
							double_print(0,1,out,"");
							print_conversation_node(out,packet_count,conversation_count,placeholder);
						}
					}
					else
					{
						skip_current_packet = 1;
					}
				}
				/*only reset skip_current_packet*/
				if(skip_current_packet)
				{
					skip_current_packet = 0;
				}/*however, if we're not skipping....*/
				else
				{
					/*this condition exists because during mashing 
					two nodes are read in and printed simultaneously*/
					if(!argopts._mash_)
					{
						print_conversation_node(out,packet_count,conversation_count,placeholder);
					}

					last = placeholder;
					++packet_count;
				}						
			}	
	
			placeholder = placeholder->next;
		}
	}
	else
	{
		/*If we're just printing the conversation list start here....*/
		if(placeholder)
		{
			double_print(1,/*reset first_argument_condition to prevent delimitors*/
				1,/*set the comparator to true on every run*/
				out,
				"%i.] %s:%u  %s:%u\n",
				conversation_count,
				placeholder->src,
				placeholder->src_port,
				placeholder->dst,
				placeholder->dst_port);
		}
	}
	/*cleanup!*/
	if(out && !argopts._binary_dump_)
	{
		fclose(out);
	}

	++conversation_count;
}

