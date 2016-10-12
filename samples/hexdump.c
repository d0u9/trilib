#include <stdio.h>
#include <string.h>

#include "../log_level.h"
#include "../hexdump.h"

char buf1[128] = {0};
char buf2[128] = {0};
int main(void)
{
	printf("----------------------------------------------------------\n");
	char v11 = 'f', v12 = '3';
	printf("hex_to_bin('%c') = %d, hex_to_bin('%c') = %d\n",
	       v11, hex_to_bin(v11),
	       v12, hex_to_bin(v12));

	printf("----------------------------------------------------------\n");
	char v21[5] = "ffee", v22[7] = "123456";
	u8 v23[3] = {0}, v24[4] = {0};
	hex2bin(v23, v21, 2);
	hex2bin(v24, v22, 3);

	printf("hex2bin(\"%s\") = %x%x%x, hex2bin(\"%s\") = %x%x%x%x\n",
	       v21, v23[0], v23[1], v23[2], v22, v24[0], v24[1], v24[2], v24[3]);

	printf("----------------------------------------------------------\n");
	char v31[5] = {0}, v32[7] = {0};
	bin2hex(v31, v23, 2);
	bin2hex(v32, v24, 3);
	printf("bin2hex(\"%s\") = %s, bin2hex(\"%s\") = %s\n", v21, v31, v22, v32);

	printf("----------------------------------------------------------\n");
	memset(buf1, 0, 128);
	hex_dump_to_buffer((void *)&v11, 64, 32, 1, buf1, 128, TRUE);
	printf("%s\n", buf1);

	printf("----------------------------------------------------------\n");
	print_hex_dump(LOG_DEBUG, "raw data: ", DUMP_PREFIX_ADDRESS,
			16, 1, (void *)&v32, 128, TRUE);

	return 0;
}
