#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
int sig1 = 0, sig2 = 0;

void usr_handle(int sig) {
	if (sig == SIGUSR1)
		sig1++;
	else if (sig == SIGUSR2) 
		sig2++;
}

void term_handle(int sig) {
	if (sig == SIGTERM) {
		printf("%d %d\n", sig1, sig2);
		exit(0);
	}
}


int main () {
	struct sigaction s1;
	s1.sa_handler = usr_handle;
	if (sigaction(SIGUSR1, &s1, NULL) < 0) 
		fprintf(stderr, "error setting sigusr1\n");
	if (sigaction(SIGUSR2, &s1, NULL) < 0) 
		fprintf(stderr, "error setting sigusr2\n");
	s1.sa_handler = term_handle;
	if (sigaction(SIGTERM, &s1, NULL) < 0) 
		fprintf(stderr, "error setting sigterm\n");
	while (1);
	return 0;
}
