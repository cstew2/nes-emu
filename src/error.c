#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#include "error.h"
#include "debug.h"

void check_memory(void const *p)
{
	if(p == NULL) {
		log_err("ERROR: Could not allocate memory\n");
		exit(-1);
	}
}

void check_errno(void)
{
	if(errno != 0) {
		log_err("Error: %s\n", strerror(errno));
		exit(-1);
	}
}

void check_return(int ret, const char *messages)
{
	if(ret) {
		log_err("Error: %s\n", messages);
	}
}
