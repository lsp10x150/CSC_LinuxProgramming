#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

int filter(const struct dirent* dir) {
	const char* name = dir->d_name;
	int i = 0;
	for (i = 0; i < strlen(name); i++) {
		if (!(0 <= name[i] - 48 && name[i] - 48 <= 9)) {
			return 0;
		}
	}
	return 1;
}

int main(int argc, char** argv) {
	int counter = 0;
	const char* toFind = "genenv";// argv[1];
	DIR* proc = opendir("/proc");
	if (proc == NULL) {
		fprintf(stderr, "error opening dir '/proc'\n");
		exit(1);
	}
	struct dirent **entry;
	int res = scandir("/proc", &entry, filter, alphasort);	
	if (res < 0) {
		fprintf(stderr, "error scanning dir\n");
	}
	// printf("processes: %d\n", res);
	int i = 0;
	for (i = 0; i < res; i++) {
		char arr[512];
		sprintf(arr, "/proc/%s/status", entry[i]->d_name);
		FILE* status = fopen(arr, "r");
		if (status == NULL) {
			fprintf(stderr, "Error opening file\n");
		}
		int reading = 1;
		char line[512];
		while (reading) {
			if (fgets(line, 512, status) == NULL) {
				fprintf(stderr, "Error in fgets\n");
			}
			if (strstr(line, "Name:") != NULL) {
				reading = 0;
				sscanf(line, "Name:\t%s\n", line);
				if (strcmp(line, toFind) == 0) 
					counter++;
			}
		}
		fclose(status);
	}
	printf("%d\n", counter);
	free(*entry); 
	return 0;
}
