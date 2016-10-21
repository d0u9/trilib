#include <stdio.h>
#include "../log_level.h"
#include "../bitmap.h"
#include "../hexdump.h"

int main(void)
{
	printf("BITS_PER_LONG = %d\n", BITS_PER_LONG);

	DECLARE_BITMAP(bits1, 12);
	DECLARE_BITMAP(bits2, 100);
	DECLARE_BITMAP(tmp, 128);

	printf("zero \n");
	bitmap_zero(bits1, 12);
	bitmap_zero(bits2, 100);
	print_hex_dump("", " bits1 ", DUMP_PREFIX_ADDRESS, 16, 8, bits1, 16, TRUE);
	print_hex_dump("", " bits2 ", DUMP_PREFIX_ADDRESS, 16, 8, bits2, 16, TRUE);

	printf("fill \n");
	bitmap_fill(bits1, 12);
	bitmap_fill(bits2, 100);
	print_hex_dump("", " bits1 ", DUMP_PREFIX_ADDRESS, 16, 8, bits1, 16, TRUE);
	print_hex_dump("", " bits2 ", DUMP_PREFIX_ADDRESS, 16, 8, bits2, 16, TRUE);

	printf("copy bits2 to tmp\n");
	bitmap_zero(tmp, 128);
	bitmap_copy(tmp, bits2, 100);
	print_hex_dump("", " tmp   ", DUMP_PREFIX_ADDRESS, 16, 8, tmp, 16, TRUE);
	print_hex_dump("", " bits2 ", DUMP_PREFIX_ADDRESS, 16, 8, bits2, 16, TRUE);

	printf("set bit0 in tmp\n");
	bitmap_zero(tmp, 128);
	set_bit(0, tmp);
	print_hex_dump("", " tmp   ", DUMP_PREFIX_ADDRESS, 16, 8, tmp, 16, TRUE);

	printf("set bit63 in tmp\n");
	set_bit(63, tmp);
	print_hex_dump("", " tmp   ", DUMP_PREFIX_ADDRESS, 16, 8, tmp, 16, TRUE);

	printf("set bit100 in tmp\n");
	set_bit(100, tmp);
	print_hex_dump("", " tmp   ", DUMP_PREFIX_ADDRESS, 16, 8, tmp, 16, TRUE);

	printf("set bit64 in tmp\n");
	set_bit(64, tmp);
	print_hex_dump("", " tmp   ", DUMP_PREFIX_ADDRESS, 16, 8, tmp, 16, TRUE);

	printf("clear bit63 in tmp\n");
	clear_bit(63, tmp);
	print_hex_dump("", " tmp   ", DUMP_PREFIX_ADDRESS, 16, 8, tmp, 16, TRUE);

	printf("find_first_bit(tmp, 128) = %lu\n", find_first_bit(tmp, 128));

	printf("clear bit0 in tmp\n");
	clear_bit(0, tmp);
	print_hex_dump("", " tmp   ", DUMP_PREFIX_ADDRESS, 16, 8, tmp, 16, TRUE);
	printf("find_first_bit(tmp, 128) = %lu\n", find_first_bit(tmp, 128));

	printf("test bit100 in tmp");
	printf(" test_bit(100, tmp) = %d\n", test_bit(100, tmp));
	printf("test bit99 in tmp");
	printf(" test_bit(99, tmp) = %d\n", test_bit(99, tmp));

	return 0;
}
