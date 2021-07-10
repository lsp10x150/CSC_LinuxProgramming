#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>

void handle_urg(int sig) {
	exit(0);
}

void demonize() {
	pid_t pid = fork();
	if (pid == 0) {
		if (chdir("/") < 0) {
			fprintf(stderr, "error chdir\n");
			exit(1);
		}
		setsid();
		fclose(stdin);
		fclose(stderr);
		fclose(stdout);
		struct sigaction s;
		s.sa_handler = handle_urg;
		if (sigaction(SIGURG, &s, NULL) < 0) {
			fprintf(stderr, "Error performing sigaction\n");
			exit(1);
		}
		pause();
	} else {
		printf("%d\n", pid);
	}
}

int main() {
	demonize();
}
