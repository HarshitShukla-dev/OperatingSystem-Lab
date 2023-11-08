#include <unistd.h>

int main()
{
	char buff[20];
	read(0, buff, 5);
	write(1, buff, 15);
	return 0;
}
