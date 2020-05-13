#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include <string.h>

#include "debug.h"

FILE *LOG_FP;
time_t LOG_NOW;
char *LOG_DATE;

bool DEBUG_ON = false;

const char *LOG_FILE = "./nes.log";

void log_init(bool debug)
{
	fclose(fopen(LOG_FILE, "w"));
	LOG_NOW = 0;
	LOG_DATE = NULL;
	LOG_FP = NULL;
	LOG_FP = fopen(LOG_FILE, "a");
	if(LOG_FP == NULL) {
		log_msg(WARN, "debug messages cannot be written to a file.\n");
		return;
	}
	DEBUG_ON = debug;
	LOG_NOW = time(NULL);
	LOG_DATE = ctime(&LOG_NOW);
	log_msg(INFO, "Opened Log file: %s\n", LOG_FILE);
}

void log_term(void)
{
	fclose(LOG_FP);
}

void log_msg(LOG_LEVEL level, const char *fmt, ...)
{
	if(DEBUG_ON) {
		if(fmt != NULL) {
			va_list args;
			va_list file_args;
			va_start(args, fmt);
			va_copy(file_args, args);
			
			LOG_NOW = time(NULL);
			LOG_DATE = strtok(ctime(&LOG_NOW), "\n");
			int size = ((sizeof(char) * strlen(fmt)) +
				    (sizeof(char) * 12) +
				    (sizeof(char) * strlen(LOG_DATE)));
			char *mod_fmt = malloc(size);
			switch(level) {
 			case INFO:
				strcpy(mod_fmt, LOG_DATE);
				strcat(mod_fmt, " - INFO: ");
				strcat(mod_fmt, fmt);
				vfprintf(stdout, mod_fmt, args);
				break;
			case WARN:
				strcpy(mod_fmt, LOG_DATE);
				strcat(mod_fmt, " - WARN: ");
				strcat(mod_fmt, fmt);
				vfprintf(stdout, mod_fmt, args);
				break;
			case ERROR:
				strcpy(mod_fmt, LOG_DATE);
				strcat(mod_fmt, " - ERROR: ");
				strcat(mod_fmt, fmt);
				vfprintf(stderr, mod_fmt, args);
				break;
			default:
				strcpy(mod_fmt, LOG_DATE);
				strcat(mod_fmt, " - INFO: ");
				strcat(mod_fmt, fmt);
				vfprintf(stdout, mod_fmt, args);
				break;
			}
			va_end(args);
			if(LOG_FP != NULL) {
			        vfprintf(LOG_FP, mod_fmt, file_args); 
			}
			va_end(file_args);
			free(mod_fmt);
		}
	}
}
