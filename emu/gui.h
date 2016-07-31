#ifndef GUI_H
#define GUI_H

#include <X11/X.h>
#include <X11/Xlib.h>

#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>
#include <GL/glut.h>

int main_gui(void);
int draw_black(void);

int open_code(void);
int open_hex(void);

#endif
