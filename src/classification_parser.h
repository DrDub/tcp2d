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

#ifndef _CLASSIFICATION_PARSER_
#define _CLASSIFICATION_PARSER_

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "classification.h"

//Boring error function for parsing failures
void conversation_rule_error(const char /*error msg*/
			, char * /*rule being parsed during error*/);

//Read classification rules from argopts and attach them to classification_rules
void process_classification_rules(char *);

#endif
