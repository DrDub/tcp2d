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


#include "argopts.h"

struct argopts argopts = 
{
	._text_payload_ = 0,
	._hex_payload_ = 0,
	._mash_ = 0,
	._arff_ = 0,
	._header_ = 1,

	._print_payload_ = 0,
	._print_timestamp_=0,
	._print_seq_=0,
	._print_ack_=0,
	._print_src_ip_=0,
	._print_dst_ip_=0,
	._print_src_port_=0,
	._print_dst_port_=0,

        ._print_res1_=0,
        ._print_doff_=0,
        ._print_fin_flag_=0,
        ._print_syn_flag_=0,
        ._print_rst_flag_=0,
        ._print_psh_flag_=0,
        ._print_ack_flag_=0,
        ._print_urg_flag_=0,
        ._print_res2_=0,

        ._print_window_=0,
        ._print_check_=0,
        ._print_urg_ptr_=0,

        ._print_ip_v_=0,
        ._print_ip_hl_=0,
        ._print_ip_tos_=0,
        ._print_ip_len_=0,
        ._print_ip_id_=0,
        ._print_ip_off_=0,
        ._print_ip_ttl_=0,
        ._print_ip_p_=0,
        ._print_ip_sum_=0,

	._list_conversations_ = 0,
	._split_output_ = 0,
	._drop_duplicates_ = 1,
	._no_wrap_ = 0,
	._quiet_ = 0,

	._delimitor_ = ",",
	._format_ = "default;",
	._classification_rules_ = 0,
	._default_label_ = "-",
	._binary_dump_ = 0,

	._filename_ = 0,
	._outfile_ = 0
};

static struct option long_options[] = 
{
	{"filename",required_argument,0,'f' },
        {"text-payload",no_argument,0,'T'},
	{"hex-payload",no_argument,0,'X'},
	{"mash",no_argument,0,'M'},
	{"list-conversations",no_argument,0,'L'},
	{"delimitor",required_argument,0,'d'},
	{"format",required_argument,0,'f'},
	{"output",required_argument,0,'o'},
	{"binary-dump",no_argument,0,'B'},
	{"split-output",no_argument,0,'S'},
        {"keep-duplicates",no_argument,0,'D'},
	{"no-wrap",no_argument,0,'N'},
	{"arff",no_argument,0,'A'},
	{"no-header",no_argument,0,'H'},
	{"quiet",no_argument,0,'Q'},
	{"help",no_argument,0,'?'},
        {0,0,0,0}
};

void print_usage()
{
	printf("tcp2d :: Author: Morgan Phillips (winter2718@gmail.com) (http://k8pl.us)\n\n");
	printf("Warning: This program is still early in development and is not well tested.\n\n");
	printf("tcp2d is a program for building usable data sets in csv or arff format out of TCP streams.\n");
 	printf("TCP packets are reassembled, and duplicates dropped, by default.\n\n");
	printf("Options with arguments:\n");
	printf("-f --filename     	  (path to a packet capture file to be used)\n");
	printf("-o --output 	  	  (name/path to an output file)\n");
	printf("-d --delimitor	  	  (change the field delimitor, default is ',')\n");
	printf("-c --classification-rules (allows classification of individual packets)\n");
	printf("-m --format	  	  (change the fields displayed)\n\n");
	
	printf("format example: -m 'srcip;dstip;tcpflags;ip_len;payload;'\n");
	printf("will output the source ip, destination ip, tcp flags, ip length, and payload.\n");
	printf("All data available in the header structs from netinet/ip.h and netinet/tcp.h is");
	printf("available and generally follows the naming convention of the struct variable name");
	printf("(i.e. ip_len) and must be followed by a semicolon.\n\n");
		
	printf("Flags:\n");
	printf("-L --list-conversations (shows all tcp conversations available in a data set)\n");
	printf("-A --arff-header  /in development/(adds an arff header to the top of any output)\n");
	printf("-H --no-header	  /in development/(disables column headings)\n");
	printf("-T --text-payload (remove all non-printable values from payloads)\n");
	printf("-X --hex-payload  (show all payloads as hex, most useful for document classification of payloads)\n");
	printf("-S --split-output (split output streams into individual files)\n");
	printf("-M --mash	  (print requests and responses on a single line)\n");
	printf("-B --binary-dump  (dumps binary payloads from streams into indidual files for pcap mining)\n");
	printf("-D --keep-duplicates (turns off dropping of duplicate packets)\n");
	printf("-Q --quiet	  (disable stdout)\n");
	printf("-N --no-wrap	  (print results as a single line)\n");
}

int process_opts(int argc, char ** argv)
{
	int long_index,c;
        while ((c = getopt_long(argc, argv,"?TXMLDNAHQf:d:m:BSo:c:", 
                   long_options, &long_index )) != -1)
        {
                switch (c)
                {
                        case 'T':
                                argopts._text_payload_ = 1;
                                break;
			case 'X':
				argopts._hex_payload_ = 1;
				break;
			case 'M':
				argopts._mash_ = 1;
				break;
			case 'D':
				argopts._drop_duplicates_ = 0;
				break;
			case 'L':
				argopts._list_conversations_ = 1;
				break;
			case 'd':
				argopts._delimitor_ = optarg;
				break;
                        case 'f':
                                argopts._filename_ = optarg;
                                break;
			case 'o':
				argopts._outfile_ = optarg;
				break;
			case 'c':
				argopts._classification_rules_ = optarg;
				break;
			case 'B':
				argopts._binary_dump_ = 1;
				argopts._split_output_ = 1;
				argopts._print_payload_ = 1;
				argopts._drop_duplicates_ = 1;
				break;
			case 'm':
				argopts._format_ = optarg;
				break;
			case 'S':
				argopts._split_output_ = 1;
				break;
			case 'N':
				argopts._no_wrap_ = 1;
				break;
			case 'A':
				argopts._arff_ = 1;
				break;
			case 'H':
				argopts._header_ = 0;
				break;
			case 'Q':
				argopts._quiet_ = 1;
				break;
			case '?':
				print_usage();
				exit(0);
                        default:
				print_usage();
				exit(0);
                }
        }

	process_format_string(argopts._format_);
	if(argopts._classification_rules_)
	{
		process_classification_rules(argopts._classification_rules_);
	}
	return 1;
}

