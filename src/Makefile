CC=gcc
CFLAGS=-lpcap -std=gnu99 -g

tcp2d:  tcp2d.o process.o argopts.o argopts_format.o more_args.o classification.o classification_parser.o conversation.o conversation_header.o conversation_print.o payload.o conversation_list.o
	$(CC) tcp2d.o process.o argopts.o argopts_format.o more_args.o classification.o classification_parser.o conversation.o conversation_header.o conversation_print.o payload.o conversation_list.o -o ../tcp2d $(CFLAGS)

clean:
	rm -rf *o ../tcp2d

