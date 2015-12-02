#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#include "debug.h"

void debug_message(const char *message, ...)
{
	if(debug_on) {
		if(message != NULL) {
			va_list args;
			va_start (args, message);
			vfprintf(stderr, message, args);
			va_end (args);
		}
	}
}

void log_info(const char *message, ...)
{
	if(debug_on) {
		if(message != NULL) {
			va_list args;
			va_start (args, message);
			vfprintf(stderr, message, args);
			FILE *fp = fopen("./log", "w");
			if(fp != NULL && ferror(fp)) {
				vfprintf(fp, message, args);
			}
			va_end (args);
			fclose(fp);
		}
	}
}

void log_warm(const char *message, ...)
{
	if(debug_on) {
		if(message != NULL) {
			va_list args;
			va_start (args, message);
			vfprintf(stderr, message, args);
			FILE *fp = fopen("./log", "w");
			if(fp != NULL && ferror(fp)) {
				vfprintf(fp, message, args);
			}
			va_end (args);
			fclose(fp);
		}
	}
}

void log_err(const char *message, ...)
{
	if(debug_on) {
		if(message != NULL) {
			va_list args;
			va_start (args, message);
			vprintf (message, args);
			va_end (args);
			vfprintf(stderr, message, args);
			FILE *fp = fopen("./log", "w");
			if(fp != NULL && ferror(fp)) {
				vfprintf(fp, message, args);
			}
			va_end (args);
			fclose(fp);
		}
	}
}
