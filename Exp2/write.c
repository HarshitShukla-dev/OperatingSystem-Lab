#include <unistd.h>
#include <stdio.h>

int main() {
	int n;
	n = write(1, "Hello world", 7);
	printf("\nTotal number of bytes : %d ", n);
	return 0;
}
