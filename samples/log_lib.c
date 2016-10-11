#include "log_lib.h"

#include "../log_level.h"

#define DEBUG
/*#define LOG_LEVEL LOG_INFO*/
/*#define LOG_DIS_STD_PREFIX_LINE*/

#include "../log.h"

int add(int a, int b)
{
	int c = a + b;
	printl_debug("debug info can be only seen when log level = LOG_DEBUG\n");
	printl_debug("debug c = a + b = %d + %d = %d\n", a ,b, c);

	printl_warning("warning, you can control the printed info by defining macros before the including of log.h\n\n");

	return c;
}

