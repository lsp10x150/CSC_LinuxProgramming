#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>
#include <string.h>

int main(int argc, char** argv) {
	struct sockaddr_in sock;
	int s = socket(AF_INET, SOCK_DGRAM, 0);
	inet_aton("127.0.0.1", &sock.sin_addr);
	sock.sin_port = htons(atoi(argv[1]));
	sock.sin_family = AF_INET;

	int result = bind(s, (struct sockaddr*) &sock, sizeof(sock));
	if (result < 0) return 1;
	
	char buf[10240];
	int recieved = 0;
	while (recieved = recvfrom(s, buf, 5120, 0, NULL, NULL)) {
		if (strncmp(buf, "OFF\n", 4) == 0) break;
		printf("%s\n", buf);	
		int i = 0;
		for (i = 0; i < recieved; i++) 
			buf[i] = 0;
	}
	return 0;
}
