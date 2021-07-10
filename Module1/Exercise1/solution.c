#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <dlfcn.h>
#include <stdlib.h>

int (*f_prototype)(int);

bool init_lib(const char* lib_name, const char* func_name) {
	void *hdl = dlopen(lib_name, RTLD_LAZY);
	if (NULL == hdl) return false;
	f_prototype = (int (*)(int))dlsym(hdl, func_name);
	if (NULL == f_prototype) return false;
	return true;
}

int main(int argc, char** argv) {
	const char *lib = argv[1], *func = argv[2];
	int arg = atoi(argv[3]);
	init_lib(lib, func);
	printf("%d\n", f_prototype(arg));
}
