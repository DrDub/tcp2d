CC=gcc
CFLAGS=-lpcap -g -w

tcp2d:  tcp2d.o process.o payload.o argopts.o argopts_format.o classification.o classification_parser.o conversation.o conversation_header.o conversation_print.o conversation_list.o
	$(CC) tcp2d.o process.o payload.o argopts.o argopts_format.o classification.o classification_parser.o conversation.o conversation_header.o conversation_print.o conversation_list.o -o ../tcp2d $(CFLAGS)

clean:
	rm -rf *o ../tcp2d
