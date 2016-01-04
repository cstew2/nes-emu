#ifndef DEBUG_H
#define DEBUG_H

#include <stdio.h>
#include <stdbool.h>

bool debug_on;
FILE *fp;

/* function prototypes */
void debug_init(void);

void debug_message(const char *message, ...);
void log_info(const char *message, ...);
void log_warm(const char *message, ...);
void log_err(const char *message, ...);

#endif
