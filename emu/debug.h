#ifndef DEBUG_H
#define DEBUG_H

#include <stdio.h>
#include <stdbool.h>

typedef enum {
	INFO,
	WARN,
	ERROR
}LOG_LEVEL;

/* function prototypes */
void log_init(bool debug);
void log_term(void);
void log_msg(LOG_LEVEL level, const char *fmt, ...);

#endif
