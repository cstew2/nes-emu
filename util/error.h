#ifndef ERROR_H
#define ERROR_H

/* function prototype */
void check_memory(void const *p);
void check_errno(void);
void check_return(int ret, const char *message);

#endif

