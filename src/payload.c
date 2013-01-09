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


#include "payload.h"

void strip_non_printable(char * payload)
{
	int i =0;
	int char_seen=0;
	while(i < strlen(payload))
	{	
		if(isprint(payload[i]) > 0)
		{		
			payload[char_seen] = payload[i];
			++char_seen;
		}
		++i;
	}

	while(char_seen < strlen(payload))
	{
		payload[char_seen] = 0;
		char_seen++;
	}
        
}

void binary_to_printable(char * payload)
{
	
	int i = 0;
	char * buffer = malloc(sizeof(char)*strlen(payload)*4);
	while(i < strlen(payload))
	{
		unsigned int high = (payload[i] >> 4) & 0xf;
		unsigned int low = (payload[i] & 0xf);
		
		sprintf(buffer+strlen(buffer),"%x%x",high,low);
		
		if((i+1)%2 == 0)
		{
			sprintf(buffer+strlen(buffer)," ");
		}

		++i;
	}
	memmove(payload,buffer,sizeof(char)*strlen(payload)*2);	
}

