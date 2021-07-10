#include <stdio.h>

int stringStat(const char *string, size_t multiplier, int *count);
const char* hello = "Hello";

int main () {
	int b = 11;
	int a = stringStat(hello, 10, &b);
	printf("a=%d (expected 50) and b=%d (expected 12)\n", a, b);
}
