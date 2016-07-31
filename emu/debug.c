#include <stdlib.h>
#include <stdarg.h>

#include "debug.h"

static FILE *fp;

void debug_init(void)
{
	const char *filepath = "./cnes.log";
	
	fp = fopen(filepath, "w");
}

void debug_term(void)
{
	fclose(fp);
}

void debug_message(const char *message, ...)
{
	if(debug_on) {
		if(message != NULL) {
			va_list args;
			va_start(args, message);
			vfprintf(stderr, message, args);
			va_end(args);
		}
	}
}

void log_info(const char *message, ...)
{
	if(debug_on) {
		if(message != NULL) {
			va_list args;
			va_start(args, message);
			vfprintf(stderr, message, args);
			if(fp != NULL && ferror(fp)) {
				vfprintf(fp, message, args);
			}
			va_end(args);
		}
	}
}

void log_warn(const char *message, ...)
{
	if(debug_on) {
		if(message != NULL) {
			va_list args;
			va_start(args, message);
			vfprintf(stderr, message, args);
			if(fp != NULL && ferror(fp)) {
				vfprintf(fp, message, args);
			}
			va_end(args);
		}
	}
}

void log_err(const char *message, ...)
{
	if(debug_on) {
		if(message != NULL) {
			va_list args;
			va_start(args, message);
			vprintf(message, args);
			va_end(args);
			vfprintf(stderr, message, args);
			if(fp != NULL && ferror(fp)) {
				vfprintf(fp, message, args);
			}
			va_end(args);
		}
	}
}
