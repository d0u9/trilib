/**
 * licensed under GPL 2.0
 * @d0u9
 */
#include "log.h"

const char *__log_level_str[] = {
				"EMERG",
				"ALERT",
				"CRIT",
				"ERR",
				"WARN",
				"NOTICE",
				"INFO",
				"DEBUG"
				};

#ifdef LOG_EN_FILE_LOG
FILE *__log_file_fp = NULL;
#endif

#ifdef LOG_EN_FILE_LOG
int init_log(const char *path, const char *mode)
{
	__log_file_fp = fopen(path, mode);
	return 0;
}
#endif


#ifdef LOG_EN_FILE_LOG
void exit_log(void)
{
	fclose(__log_file_fp);
}
#endif


