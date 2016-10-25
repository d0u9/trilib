# LOG module

## Introduction

A preprocessor macro controlled log module.

Users are allowed to control all the details of log information with defining
appropriate macros.

## Setting Options

Here is a full list of macros:

```
#define LOG_EN_FILE_LOG
#define LOG_DIS_COLOR
#define LOG_EN_STD_LEVEL_NUM

#define LOG_LEVEL LOG_INFO
#define LOG_STD_LEVEL LOG_ERR
#define LOG_FILE_LEVEL LOG_CRIT

#define LOG_EN_PREFIX_PID
#define LOG_EN_PREFIX_TID

#define LOG_DIS_FILE_PREFIX_TIME
#define LOG_DIS_FILE_PREFIX_FILE
#define LOG_DIS_FILE_PREFIX_LINE
#define LOG_DIS_FILE_PREFIX_LEVEL
#define LOG_DIS_FILE_PREFIX_PID
#define LOG_DIS_FILE_PREFIX_TID

#define LOG_DIS_STD_PREFIX_TIME
#define LOG_DIS_STD_PREFIX_FILE
#define LOG_DIS_STD_PREFIX_LINE
#define LOG_DIS_STD_PREFIX_LEVEL
#define LOG_DIS_STD_PREFIX_PID
#define LOG_DIS_STD_PREFIX_TID

#define LOG_DIS_PREFIX_TIME
#define LOG_DIS_PREFIX_FILE
#define LOG_DIS_PREFIX_LINE
#define LOG_DIS_PREFIX_LEVEL
#define LOG_DIS_PREFIX_PID
#define LOG_DIS_PREFIX_TID
```

## Default Behavior

By default, log to file function is disabled. Define `LOG_EN_FILE_LOG`
macro to enable file logging. It is better to define this macro globally,
e.g. add `-DLOG_EN_FILE_LOG` option to gcc. It is due to the fact that
this behavior affects each source files in your project.

Another noticeable fact is that the thread implementation is variable according
to the platform. In other word, besides `pthread` implementation, there exist
some other thread libraries, such as Apple's Grand Central Dispatch(GCD).If you
happen to use these libs. You should modify the `get_tid()` function.

Print **PID** and **TID** is disabled by default, most of time, they are
useless. But you can enable them anytime by defining `LOG_EN_PREFIX_PID`
and `LOG_EN_PREFIX_TID`.

The defalut log level is `notice`, which measn debug information won't be
printed unless you defined `DEBUG` macro somewhere.


## ScreenShots

![](pics/log1.png)

## API

```
init_log(const char *path, const char *mode)
```

Open and init log file. If no LOG_EN_FILE_LOG macro is set, this function will
be compiled to an empty function, it means that there is no need to delete this
function if you do not want to use the function of log to file.

- `path`: is a string which contains the path to log file.
- `mode`: is same as the fopen()'s mode parameter.

```
exit_log(void)
```

Close log file and release related resources. if no LOG_EN_FILE_LOG macro is
set, this function will be compiled to an empty function.

```
printl(level, fmt, ...)
```

Dump a message to stdout, you have to specific the log level here as the first
parameter, all available level definitations can be found in *log_level.h*.

- `level`: the log level, can be found in *log_level.h*.
- `fmt`: the format string, act as printf().

```
printl_emerg(fmt, ...)
printl_alert(fmt, ...)
printl_crit(fmt, ...)
printl_err(fmt, ...)
printl_warning(fmt, ...)
printl_notice(fmt, ...)
printl_info(fmt, ...)
printl_debug(fmt, ...)
```

Act as `printl()` but log level.

