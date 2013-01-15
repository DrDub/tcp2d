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


#include "conversation_header.h"

struct header_values csv_header_values =
{
	.payload = "payload",
	.ts = "timestamp",
	.seq = "seq_number",
	.ack = "ack_number",
	.src = "src_ip",
	.src_port = "src_port",
	.dst = "dst_ip",
	.dst_port = "dst_port",
	.res1 = "res1",
	.doff = "doff",
	.fin_flag = "fin",
	.syn_flag = "syn",
	.rst_flag = "rst",
	.psh_flag = "psh",
	.ack_flag = "ack",
	.urg_flag = "urg",
	.res2 = "res2",
	.window = "window",
	.check = "check",
	.urg_ptr = "urg_ptr",
	.ip_v = "ip_v",
	.ip_hl = "ip_hl",
	.ip_tos = "ip_tos",
	.ip_len = "ip_len",
	.ip_id = "ip_id",
	.ip_off = "ip_off",
	.ip_ttl = "ip_ttl",
	.ip_p = "ip_p",
	.ip_sum = "ip_sum",
	.label = "label"
};

struct header_values mashed_csv_header_values =
{
        .payload = "response_payload",
        .ts = "response_timestamp",
        .seq = "response_seq_number",
        .ack = "response_ack_number",
        .src = "response_src_ip",
        .src_port = "response_src_port",
        .dst = "response_dst_ip",
        .dst_port = "response_dst_port",
        .res1 = "response_res1",
        .doff = "response_doff",
        .fin_flag = "response_fin",
        .syn_flag = "response_syn",
        .rst_flag = "response_rst",
        .psh_flag = "response_psh",
        .ack_flag = "response_ack",
        .urg_flag = "response_urg",
        .res2 = "response_res2",
        .window = "response_window",
        .check = "response_check",
        .urg_ptr = "response_urg_ptr",
        .ip_v = "response_ip_v",
        .ip_hl = "response_ip_hl",
        .ip_tos = "response_ip_tos",
        .ip_len = "response_ip_len",
        .ip_id = "response_ip_id",
        .ip_off = "response_ip_off",
        .ip_ttl = "response_ip_ttl",
        .ip_p = "response_ip_p",
        .ip_sum = "response_ip_sum",
	.label = "response_label"
};


/*Don't forget, this needs to be in the same order as print_conversation_node's*/
void print_conversation_header(FILE * out,_Bool mashed_header)
{
	struct header_values local_header_values;
	
	if(!argopts._arff_ && !mashed_header)
	{
		local_header_values = csv_header_values;
	}
	else if(!argopts._arff_ && mashed_header)
	{
		local_header_values = mashed_csv_header_values;
	}

	_Bool first_local_run = 1;
			
	/*payload*/
        double_print(first_local_run,argopts._print_payload_,
           	out,"%s",local_header_values.payload);
	
	first_local_run = 0;
	
	/*timestamp*/
	double_print(first_local_run,argopts._print_timestamp_,
		out,"%s",local_header_values.ts);			

	/*seq number*/
	double_print(first_local_run,argopts._print_seq_,
		out,"%s",local_header_values.seq);
			
	/*ack number*/
	double_print(first_local_run,argopts._print_ack_,
		out,"%s",local_header_values.ack);
	
	/*src ip*/
	double_print(first_local_run,argopts._print_src_ip_,
		out,"%s",local_header_values.src);
	/*src port*/
	double_print(first_local_run,argopts._print_src_port_,
		out,"%s",local_header_values.src_port);
	/*dst ip*/
	double_print(first_local_run,argopts._print_dst_ip_,
		out,"%s",local_header_values.dst);
	/*dst port*/
	double_print(first_local_run,argopts._print_dst_port_,
		out,"%s",local_header_values.dst_port);

	/*extras*/

	double_print(first_local_run,argopts._print_res1_,
		out,"%s",local_header_values.res1);
	double_print(first_local_run,argopts._print_doff_,
		out,"%s",local_header_values.doff);

	/*tcpflags*/
	double_print(first_local_run,argopts._print_fin_flag_,
		out,"%s",local_header_values.fin_flag);
	double_print(first_local_run,argopts._print_syn_flag_,
		out,"%s",local_header_values.syn_flag);
	double_print(first_local_run,argopts._print_rst_flag_,
		out,"%s",local_header_values.rst_flag);
	double_print(first_local_run,argopts._print_psh_flag_,
		out,"%s",local_header_values.psh_flag);
	double_print(first_local_run,argopts._print_ack_flag_,
		out,"%s",local_header_values.ack_flag);
	double_print(first_local_run,argopts._print_urg_flag_,
		out,"%s",local_header_values.urg_flag);
	
	double_print(first_local_run,argopts._print_res2_,
		out,"%s",local_header_values.res2);
	double_print(first_local_run,argopts._print_window_,
		out,"%s",local_header_values.window);
	double_print(first_local_run,argopts._print_check_,
		out,"%s",local_header_values.check);
	double_print(first_local_run,argopts._print_urg_ptr_,
		out,"%s",local_header_values.urg_ptr);
	double_print(first_local_run,argopts._print_ip_v_,
		out,"%s",local_header_values.ip_v);
	double_print(first_local_run,argopts._print_ip_hl_,
		out,"%s",local_header_values.ip_hl);
	double_print(first_local_run,argopts._print_ip_tos_,
		out,"%s",local_header_values.ip_tos);
	double_print(first_local_run,argopts._print_ip_len_,
		out,"%s",local_header_values.ip_len);
	double_print(first_local_run,argopts._print_ip_id_,
		out,"%s",local_header_values.ip_id);
	double_print(first_local_run,argopts._print_ip_off_,
		out,"%s",local_header_values.ip_off);
	double_print(first_local_run,argopts._print_ip_ttl_,
		out,"%s",local_header_values.ip_ttl);
	double_print(first_local_run,argopts._print_ip_p_,
		out,"%s",local_header_values.ip_p);
	double_print(first_local_run,argopts._print_ip_sum_,
		out,"%s",local_header_values.ip_sum);	

	if(argopts._classification_rules_ || argopts._classification_rules_file_)
	{
		double_print(first_local_run,1,
				out,"%s",local_header_values.label);
	}

	if(!argopts._mash_ && !mashed_header && !argopts._no_wrap_)
	{
		double_print(1,1,out,"\n");
	}
	/*when mash is on, only print newlines if this is a mashed header*/
	else if(argopts._mash_ && mashed_header && !argopts._no_wrap_)
	{
		double_print(1,1,out,"\n");
	}

}

