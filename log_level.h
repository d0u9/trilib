#ifndef _TRI_LOG_LEVEL_H
#define _TRI_LOG_LEVEL_H

#define LOG_EMERG	"0"	/* system is unusable */
#define LOG_ALERT	"1"	/* action must be taken immediately */
#define LOG_CRIT	"2"	/* critical conditions */
#define LOG_ERR		"3"	/* error conditions */
#define LOG_WARNING	"4"	/* warning conditions */
#define LOG_NOTICE	"5"	/* normal but significant condition */
#define LOG_INFO	"6"	/* informational */
#define LOG_DEBUG	"7"	/* debug-level messages */

#define LOG_LEVEL_INT(x)	((x)[0] - '0')

#endif
