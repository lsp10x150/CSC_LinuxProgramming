#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char** argv) {
    if (argc != 3) return 1;
    char arr[1024];
    const char* program =   argv[1];
    const char* param   =   argv[2];
    sprintf(arr, "./%s %s", program, param);
    FILE* process = popen(arr, "r");
    int res = 0, counter = 0;
    do {
        res = fgetc(process);
        if (res == '0') {
            counter++;
        }
    } while (res != EOF);
    pclose(process);
    return printf("%d\n", counter);
}
