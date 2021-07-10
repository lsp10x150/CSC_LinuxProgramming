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

int count_children(int pid, struct dirent** entry, int dir_size) {
    int res = 0, i;
    for (i = 0; i < dir_size; i++) {
		char arr[512];
		sprintf(arr, "/proc/%s/status", entry[i]->d_name);
		FILE* status = fopen(arr, "r");
		if (status == NULL) {
			fprintf(stderr, "Error opening file\n");
		}
		int reading = 1;
		char line[512];
		struct { int pid, ppid; } fstats = {.pid = 0, .ppid = 0};
		int gotPid = 0;
		while (reading) {
			if (fgets(line, 512, status) == NULL) {
				fprintf(stderr, "Error in fgets\n");
			}
			if (strstr(line, "Pid:") != NULL && gotPid == 0) {
				int pid = 0;
				gotPid = 1;
				sscanf(line, "Pid:\t%d\n", &pid);
				fstats.pid = pid;
			}
			if (strstr(line, "PPid:") != NULL) {
				reading = 0;
				int ppid = 0;
				sscanf(line, "PPid:\t%d\n", &ppid);
				fstats.ppid = ppid;
			}
		}
		fclose(status);
		if (fstats.ppid == pid) {
		    res += count_children(fstats.pid, entry, dir_size) + 1;
		}
	}
    return res;
}

int main(int argc, char** argv) {
	int counter = 0;
	const char* toFind = argv[1];
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
    counter = count_children(atoi(toFind), entry, res) + 1;
	printf("%d\n", counter);
	closedir(proc);
	free(*entry);
	return 0;
}
