#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <stdbool.h>

static const char key_up = '';
static const char key_down = '';
static const char key_left = '';
static const char key_right = '';
static const char key_a = '';
static const char key_b = '';
static const char key_start = '';
static const char key_select = '';

typedef struct {
	bool start;
	bool select;
	bool a_button;
	bool b_button;
	bool up;
	bool down;
	bool left;
	bool right;
}controller;

#endif
