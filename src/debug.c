#include <stdlib.h>
#include <stdio.h>

#include "debug.h"

void debug_message(const char *message)
{
	if(message != NULL) {
		fprintf(stderr, "%s", message);
	}
}

void log_info(const char *message)
{
	if(message != NULL) {
		fprintf(stderr, "INFO: %s\n", message);
		FILE *fp = fopen("./log", "r");
		if(fp != NULL && ferror(fp)) {
			fprintf(fp, "INFO: %s\n", message);
		}
	}
}

void log_warm(const char *message)
{
	if(message != NULL) {
		fprintf(stderr, "WARN: %s\n", message);
		FILE *fp = fopen("./log", "r");
		if(fp != NULL && ferror(fp)) {
			fprintf(fp, "WARN: %s\n", message);
		}
	}
}

void log_err(const char *message)
{
	if(message != NULL) {
		fprintf(stderr, "ERROR: %s\n", message);
		FILE *fp = fopen("./log", "r");
		if(fp != NULL && ferror(fp)) {
			fprintf(fp, "ERROR: %s\n", message);
		}
				
	}
}
