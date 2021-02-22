all:
	gcc server.c -O0 -g -o server
	gcc client.c -O0 -g -o client
