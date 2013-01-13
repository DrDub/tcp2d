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


#ifndef _ARGOPTS_
#define _ARGOPTS_

#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>

#include "argopts_format.h"
#include "classification_parser.h"

struct argopts
{
	char * _filename_;
	char * _outfile_;

	_Bool _wait_for_args_; /*loads pcap into memory and waits for more arguments to be passed*/
	_Bool _binary_dump_; /*overrides regular output/writes non-formatted payloads for each stream*/

        _Bool _split_output_; /*appends output to create multiple files split by conversation*/

	/*format options*/

	char * _delimitor_; /*defaults to ','*/
	char * _format_; /*data from this string is used to switch on the _print_* options*/
	char * _classification_rules_; /*a list of conversation numbers mapped to classes*/
	char * _default_label_; /* if there are no classification_rule matches */

	_Bool _text_payload_; /*strips any non-printable characters from a payload using isprint()*/
	_Bool _hex_payload_; /*converts each byte of a payload to a hex representation*/

	_Bool _mash_; /*prints requests and responses on a single line*/
	
	/*defaults*/
	_Bool _print_payload_;
	_Bool _print_timestamp_;
	_Bool _print_seq_;
	_Bool _print_ack_;
	_Bool _print_src_ip_;
	_Bool _print_dst_ip_;
	_Bool _print_src_port_;
	_Bool _print_dst_port_;
        
	/*tcp-ip extras*/
	_Bool _print_res1_;
        _Bool _print_doff_;
        _Bool _print_fin_flag_;
        _Bool _print_syn_flag_;
        _Bool _print_rst_flag_;
        _Bool _print_psh_flag_;
        _Bool _print_ack_flag_;
        _Bool _print_urg_flag_;
        _Bool _print_res2_;

        _Bool _print_window_;
        _Bool _print_check_;
        _Bool _print_urg_ptr_;

        _Bool _print_ip_v_;
        _Bool _print_ip_hl_;
        _Bool _print_ip_tos_;
        _Bool _print_ip_len_;
        _Bool _print_ip_id_;
        _Bool _print_ip_off_;
        _Bool _print_ip_ttl_;
        _Bool _print_ip_p_;
        _Bool _print_ip_sum_;

	_Bool _arff_; /*generate an arff type header (otherwise csv by default)*/
	_Bool _header_; /*print a header*/
	_Bool _list_conversations_; /*overrides output to create a list of conversation numbers*/
        _Bool _drop_duplicates_;  /*frees packets with preexisting seq-ack combos*/
	_Bool _no_wrap_;	/*stops newlines from being added at the end of a conversation packet*/
	_Bool _quiet_;		/*turns off console output*/

};

extern struct argopts argopts;

int process_opts(int, char **);

#endif
