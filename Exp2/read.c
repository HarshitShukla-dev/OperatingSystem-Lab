#include <unistd.h>
#include <stdio.h>

int main(){
	char buff[20];
	int n;
	n = read(0, buff, 10);
	write(1, buff, n);
	printf("\nTotal number of bytes : %d", n);
	return 0;
}
