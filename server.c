#include <sys/socket.h>
#include <err.h>

#include "server.h"

int main(){
	int sk, ret;
	struct sockaddr_un name = {0};
	char *c;
	int client_sk;
	char buffer[BUFSZ] = {0};

	sk = socket(AF_UNIX, SOCK_STREAM, 0);
	if (sk<0)
		err(-1, "Unable to create socket");
	name.sun_family = AF_UNIX;
	strncpy(name.sun_path, PATH, sizeof(PATH));
	if ((ret=bind(sk, (struct sockaddr*)&name, sizeof(name)))<0){
		close(sk);
		err(-1, "Unable to bind socket");
	}
	if (listen(sk, 5)<0){
		close(sk);
		err(-1, "Unable to set up socket");
	}
	while (1){
		if ((client_sk = accept(sk, NULL, NULL))<0){
			close(sk);
			err(-1, "Unable to accept");
		}
		ret = read(client_sk, buffer, BUFSZ);
		if (ret<0||ret>BUFSZ){
			close(sk);
			err(-1, "Error in buffer reading");
		}
		c=strstr(buffer, " ");
		if (c!=NULL){
			*c = 0;
		}
		if (!strcmp(buffer, "EXIT")){
			close(client_sk);
			close(sk);
			exit(0);
		}
		if (!strcmp(buffer, "PRINT")){
			*c = ' ';
			printf("%d", *(c+1));
		}
	}
	return 0;
}
