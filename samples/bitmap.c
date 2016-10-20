#include <stdio.h>
#include "../bitmap.h"

int main(void)
{
	printf("BITS_PER_LONG = %d\n", BITS_PER_LONG);

	DECLARE_BITMAP(bits1, 12);
	DECLARE_BITMAP(bits2, 128);

	bitmap_zero(bits1, 12);
	bitmap_zero(bits2, 128);

	bitmap_fill(bits1, 12);
	bitmap_fill(bits2, 128);

	return 0;
}
