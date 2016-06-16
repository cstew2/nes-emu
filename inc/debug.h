#ifndef DEBUG_H
#define DEBUG_H

#include <stdio.h>
#include <stdbool.h>

bool debug_on;

/* function prototypes */
void debug_init(void);

void debug_message(const char *message, ...);
void log_info(const char *message, ...);
void log_warn(const char *message, ...);
void log_err(const char *message, ...);

#endif
