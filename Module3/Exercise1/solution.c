#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

int main() {
	char arr[1024];
	FILE* file = fopen("/proc/self/status", "r");
	if (file == NULL) {
		fprintf(stderr, "couldn't open /proc/self/status");
		return 1; 
	}
	bool reading = true;
	while (reading) {
		fgets(arr, 1024, file);
		char* found = strstr(arr, "PPid");
		if (found != NULL) {
			int ppid = 0;
			sscanf(arr, "PPid:\t%d", &ppid);
			printf("%d\n", ppid);
			reading = false;
		}	
	}
	if (fclose(file)) 
		fprintf(stderr, "error closing status\n");
}
