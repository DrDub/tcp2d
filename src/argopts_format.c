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


#include "argopts_format.h"

void quick_switch(char * format, const char * search, _Bool * option,_Bool option_value)
{
	if(strstr(format,search))
	{
		*option = option_value;
	}
}

void process_format_string(char * format)
{
	if(strstr(format,"default;"))
	{
		argopts._print_timestamp_ = 1;
		argopts._print_seq_ = 1;
		argopts._print_ack_ = 1;
		argopts._print_src_ip_ = 1;
		argopts._print_src_port_ = 1;
		argopts._print_dst_ip_ = 1;
		argopts._print_dst_port_ = 1;		
	}
	if(strstr(format,"tcpflags;"))
	{
		argopts._print_fin_flag_ = 1;
        	argopts._print_syn_flag_ = 1;
        	argopts._print_rst_flag_ = 1;
        	argopts._print_psh_flag_ = 1;
        	argopts._print_ack_flag_ = 1;
        	argopts._print_urg_flag_ = 1;
	}

	quick_switch(format,"payload;",&argopts._print_payload_,1);
	quick_switch(format,"ts;",&argopts._print_timestamp_,1);
	quick_switch(format,"seq;",&argopts._print_seq_,1);
	quick_switch(format,"ack;",&argopts._print_ack_,1);
	quick_switch(format,"srcip;",&argopts._print_src_ip_,1);
	quick_switch(format,"dstip;",&argopts._print_dst_ip_,1);
	quick_switch(format,"srcport;",&argopts._print_src_port_,1);
	quick_switch(format,"dstport;",&argopts._print_dst_port_,1);
        quick_switch(format,"res1;",&argopts._print_res1_,1);
        quick_switch(format,"doff;",&argopts._print_doff_,1);
        quick_switch(format,"finflag;",&argopts._print_fin_flag_,1);
        quick_switch(format,"synflag;",&argopts._print_syn_flag_,1);
        quick_switch(format,"rstflag;",&argopts._print_rst_flag_,1);
        quick_switch(format,"pshflag;",&argopts._print_psh_flag_,1);
        quick_switch(format,"ackflag;",&argopts._print_ack_flag_,1);
        quick_switch(format,"urgflag;",&argopts._print_urg_flag_,1);
        quick_switch(format,"res2;",&argopts._print_res2_,1);

        quick_switch(format,"window;",&argopts._print_window_,1);
        quick_switch(format,"check;",&argopts._print_check_,1);
        quick_switch(format,"urg_ptr;",&argopts._print_urg_ptr_,1);

        quick_switch(format,"ip_v;",&argopts._print_ip_v_,1);
        quick_switch(format,"ip_hl;",&argopts._print_ip_hl_,1);
        quick_switch(format,"ip_tos;",&argopts._print_ip_tos_,1);
        quick_switch(format,"ip_len;",&argopts._print_ip_len_,1);
        quick_switch(format,"ip_id;",&argopts._print_ip_id_,1);
        quick_switch(format,"ip_off;",&argopts._print_ip_off_,1);
        quick_switch(format,"ip_ttl;",&argopts._print_ip_ttl_,1);
        quick_switch(format,"ip_p;",&argopts._print_ip_p_,1);
        quick_switch(format,"ip_sum;",&argopts._print_ip_sum_,1);
}
