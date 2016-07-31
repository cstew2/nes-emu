#include <stdio.h>
#include <stdlib.h>

#include "emu/gui.h"

int main_gui(void)
{
	// init GLUT and create Window
	char *v[1];
	v[0] = malloc(sizeof(char) *2);
	v[0] = "v";
	int c = 1;
	glutInit(&c, v);
	
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(256, 240);
	glutCreateWindow("cnes");

	draw_black();

	open_code();
	open_hex();
	
	glutMainLoop();

	return 1;
}

int draw_black(void)
{
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(0.0f, 0.0f, 0.0f);
	glRectf(-0.75f,0.75f, 0.75f, -0.75f);
	glutSwapBuffers();
	return 0;
}

int open_code(void)
{
	int id = glutCreateWindow("code");

	return id;
}

int open_hex(void)
{
	int id = glutCreateWindow("hex");

	return id;
}
