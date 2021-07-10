#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

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
		pause();
	} else {
		printf("%d\n", pid);
	}
}

int main() {
	demonize();
}
