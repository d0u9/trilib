#include <stdio.h>
#include "../color.h"

int main(void)
{
	printf("-------------------\n");

	char buf[128] = "    Hello, This is funny    ";
	if (color_string(BLACK, ON_WHITE, CROSSLINE, buf, 9) < 0) {
		printf("the buffer size is not enough\n");
		return 1;
	}

	printf("%s\n", buf);


	return 0;
}
