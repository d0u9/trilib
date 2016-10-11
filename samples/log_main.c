#include <stdio.h>

#include "../log_level.h"

/**
 * if DEBUG is defined, the default log level is set to LOG_DEBUG, otherwise,
 * is set to LOG_NOTICE
 */
#define DEBUG

//#define LOG_EN_STD_LEVEL_NUM

//#define LOG_LEVEL LOG_INFO
//#define LOG_STD_LEVEL LOG_ERR
//#define LOG_FILE_LEVEL LOG_CRIT

/*#define LOG_EN_PREFIX_PID*/
/*#define LOG_EN_PREFIX_TID*/

//#define LOG_DIS_FILE_PREFIX_TIME
//#define LOG_DIS_FILE_PREFIX_FILE
//#define LOG_DIS_FILE_PREFIX_LINE
//#define LOG_DIS_FILE_PREFIX_LEVEL
//#define LOG_DIS_FILE_PREFIX_PID
//#define LOG_DIS_FILE_PREFIX_TID

//#define LOG_DIS_STD_PREFIX_TIME
//#define LOG_DIS_STD_PREFIX_FILE
//#define LOG_DIS_STD_PREFIX_LINE
//#define LOG_DIS_STD_PREFIX_LEVEL
//#define LOG_DIS_STD_PREFIX_PID
//#define LOG_DIS_STD_PREFIX_TID

//#define LOG_DIS_PREFIX_TIME
//#define LOG_DIS_PREFIX_FILE
//#define LOG_DIS_PREFIX_LINE
//#define LOG_DIS_PREFIX_LEVEL

#include "../log.h"
#include "log_lib.h"

void *thread(void *arg)
{
	printl_debug("this is one thread, arg = %s\n", (char*)arg);
	return NULL;
}

int main(void)
{
	init_log("/tmp/log", "w");
	printf("-------------------------------------\n");

	printl(LOG_DEBUG, "debug hello %s\n", "world");
	printl_debug("debug\n");
	printl_info("info\n");
	printl_notice("notice\n");
	printl_warning("warning\n");
	printl_err("error\n");
	printl_crit("crit\n");
	printl_alert("alert\n");
	printl_emerg("emerg\n");

	add(1, 2);

	pthread_t tid;
	void *tret;
	pthread_create(&tid, NULL, thread, "hello thread");
	pthread_join(tid, &tret);

	exit_log();

	return 0;
}


