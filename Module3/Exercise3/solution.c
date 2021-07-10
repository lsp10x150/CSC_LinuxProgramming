#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

struct pd {
    int pid, ppid, tgid;
};

struct pd find_ppid_and_tgid(FILE* file) {
    char line[256];
    int reading = 3;
    struct pd res;
    while (reading) {
        if (fgets(line, 256, file) == NULL) {
            fprintf(stderr, "Error in fgets\n");
            exit(1);
        }
        if (strstr(line, "Pid") != NULL) {
            if (reading == 1) 
                reading = 0;
            else if (reading == 2) 
                reading = 1;
            else if (reading == 3) 
                reading = 2;
            sscanf(line, "Pid:\t%d", &res.pid);
        }
        if (strstr(line, "PPid") != NULL) {
            if (reading == 1) 
                reading = 0;
            else if (reading == 2) 
                reading = 1;
            else if (reading == 3) 
                reading = 2;
            sscanf(line, "PPid:\t%d", &res.ppid);
        }
        if (strstr(line, "Tgid") != NULL) {
            if (reading == 1) 
                reading = 0;
            else if (reading == 2) 
                reading = 1;
            else if (reading == 3) 
                reading = 2;
            sscanf(line, "Tgid:\t%d", &res.tgid);
        }
    }
    return res;
}

int my_pid() {
    FILE* file = fopen("/proc/self/status", "r");
	if (file == NULL) {
		fprintf(stderr, "Error opening file\n");
		exit(1);
	}
    struct pd res = find_ppid_and_tgid(file);
	fclose(file);
	return res.ppid;
}

int get_parent_id(int id) {
	char arr[1024];
	sprintf(arr, "/proc/%d/status", id);
	FILE* file = fopen(arr, "r");
	if (file == NULL) {
		fprintf(stderr, "Error opening file\n");
		exit(1);
	}
    struct pd res = find_ppid_and_tgid(file);
	fclose(file);
	if (res.pid != res.tgid) 
    	return res.tgid;
    else 
        return res.ppid;
}

int main(int argc, char** argv) {
	int id = atoi(argv[1]);
	printf("%d\n", id);
	while(id != 1) {
		id = get_parent_id(id);
		printf("%d\n", id);
	}
}
