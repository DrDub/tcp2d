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


#include "tcp2d.h"

int main(int argc,char **argv)
{

	if(process_opts(argc,argv))
	{
		pcap_t *descr;
		char errbuf[PCAP_ERRBUF_SIZE];

		//open packet capture

		if(!argopts._filename_)
		{
			printf("Please provide a capture file using: '-f'\n");
			print_usage();
			return 1;	
		}

		descr = pcap_open_offline(argopts._filename_,errbuf);
		if(descr == NULL)
		{
			printf("Could not open file: %s\n",errbuf);
			return 1;
		}
	
		//start packet processing

		if(pcap_loop(descr, 0, process, NULL) < 0)
		{
			printf("pcap_loop() failed: %s\n",errbuf);
			return 1;
		}

		print_conversation_list(tcp_conversations);

		return 0;
	}
	else
	{
		return 1;
	}
}

