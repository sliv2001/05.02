#include "server.h"

int main(){
	struct sockaddr_un name = {0};
	int sk, ret;
	char* buf;
	if ((buf=(char*)malloc(128))==NULL)
		err(-1, "Wrong malloc");
	if ((sk = socket(AF_UNIX, SOCK_STREAM, 0))<0)
		err(-1, "Unable to create socket");
	name.sun_family = AF_UNIX;
	strncpy(name.sun_path, PATH, sizeof(PATH));
	if ((ret = connect(sk, (struct sockaddr*)&name, sizeof(name)))<0)
		err(-1, "Unable to connect to socket");
	while (1){
		fgets(buf, 128, stdin);
		if (write(sk, buf, sizeof(buf))<0)
			err(-1, "Couldnot send to socket");
	}
	return 0;
}
