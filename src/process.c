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


#include "process.h"

void process(u_char *userData, const struct pcap_pkthdr* pkthdr, const u_char* packet)
{
	struct conversation * current = (struct conversation *) malloc(sizeof(struct conversation));

	const struct ether_header *etherHeader;
	const struct ip *ipHeader;
	const struct tcphdr *tcpHeader;
	struct in_addr *tmp_addr;
	char *tmp_ip;
	int src_port,dst_port;

	etherHeader= (struct ether_header*)packet;
	
	char * raw = (char *)packet+sizeof(struct ether_header)+sizeof(struct ip)+sizeof(struct tcphdr);
	char * payload = (char *)malloc(sizeof(char)*(strlen(raw)*2)+1);	
	
	memcpy(payload,raw,strlen(raw));
	current->payload = payload;

	/*See if it's an IP packet.*/	
	if(ntohs(etherHeader->ether_type) == ETHERTYPE_IP)
	{
		ipHeader= (struct ip*)(packet+sizeof(struct ether_header));
		
		/*Now make sure it's TCP*/
		if(ipHeader->ip_p == 6)
		{

			//lets grab the ports	
			tcpHeader = (struct tcphdr*)(packet+sizeof(struct ether_header)+sizeof(struct ip));
			current->src_port = ntohs(tcpHeader->source);
			current->dst_port = ntohs(tcpHeader->dest);

	                //and then convert our ip's to dot quad
			tmp_addr = (struct in_addr*)&ipHeader->ip_src;
                        tmp_ip = inet_ntoa(*tmp_addr);
			
			current->src = (char *)malloc((sizeof(char)*strlen(tmp_ip))+1);
			strncpy(current->src,tmp_ip,sizeof(char)*strlen(tmp_ip));
                        
			tmp_addr = (struct in_addr*)&ipHeader->ip_dst;
                        tmp_ip = inet_ntoa(*tmp_addr);
			
			current->dst = (char *)malloc((sizeof(char)*strlen(tmp_ip))+1);
                        strncpy(current->dst,tmp_ip,sizeof(char)*strlen(tmp_ip));

			current->seq = tcpHeader->seq;
			current->ack = tcpHeader->ack_seq;

			current->sec = pkthdr->ts.tv_sec;
			current->usec = pkthdr->ts.tv_usec;

			//Put everything else in the extra_header_info struct
			current->extra.ip_v = ipHeader->ip_v;                
        		current->extra.ip_hl = ipHeader->ip_hl;               
        		current->extra.ip_tos = ipHeader->ip_tos;                 
        		current->extra.ip_len = ipHeader->ip_len;                      
        		current->extra.ip_id = ipHeader->ip_id;                      
        		current->extra.ip_off = ipHeader->ip_off;                     
        		current->extra.ip_ttl = ipHeader->ip_ttl;                    
        		current->extra.ip_p = ipHeader->ip_p;                      
        		current->extra.ip_sum = ipHeader->ip_sum;
	
			current->extra.res1 = tcpHeader->res1;
        		current->extra.doff = tcpHeader->doff;
        		current->extra.fin = tcpHeader->fin;
        		current->extra.syn = tcpHeader->syn;
        		current->extra.rst = tcpHeader->rst;
        		current->extra.psh = tcpHeader->psh;
        		current->extra.ack = tcpHeader->ack;
        		current->extra.urg = tcpHeader->urg;
        		current->extra.res2 = tcpHeader->res2;
        		current->extra.window = tcpHeader->window;
        		current->extra.check = tcpHeader->check;
        		current->extra.urg_ptr = tcpHeader->urg_ptr;
	
			add_conversation_list(current);
		}		
	}
	else
	{	
		//Don't waste memory on non-used packets
		free(current);
	}	
}

