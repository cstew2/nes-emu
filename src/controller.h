#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <stdbool.h>
#include <stdint.h>

static const char *key_up = "\033[A";  /* 3 bytes */
static const char *key_down = "\033[B";
static const char *key_left = "\033[C";
static const char *key_right = "\033[D";
static const char key_a = 's';
static const char key_b = 'a';
static const char key_start = 13; /* carriage return*/
static const char key_select = 32; /* space */

typedef struct {
	bool a_button;
	bool b_button;
	bool select;
	bool start;
	bool up;
	bool down;
	bool left;
	bool right;
}controller;

#endif
