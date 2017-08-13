#include "Renderer.h"

//GLfloat ang3 = 1.f;
void render()
{
	glClearColor(1.f, 0.5f, 0.25f, 1.f);
	//Example1();
	Example4();
	//glClearColor(1.f, 0.5f, 0.25f, 1.f);
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	////glViewport(0, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	//glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	////glOrtho(-4.f, 4.f, -4.f, 4.f, 0.5f, 20.f);
	//SDL_TR_Perspective(60.f, 1.f, 0.1f, 20.f);

	//glBegin(GL_POLYGON);
	//glColor3f(0.f, 0.f, 0.f);
	//glVertex3f(1.f, 1.f, -2.9f);

	//glColor3f(0.f, 1.f, 0.f);
	//glVertex3f(2.f, 0.f, -2.9f);

	//glColor3f(0.f, 0.f, 1.f);
	//glVertex3f(3.f, 4.f, -2.9f);

	//glColor3f(0.f, 1.f, 1.f);
	//glVertex3f(1.f, -1.f, -2.9f);
	//glEnd();

	//glBegin(GL_POLYGON);
	//	glVertex3f(0.f, 4.f, -2.f);
	//	glVertex3f(0.f, 0.f, -2.f);
	//glEnd();
}
//void render()
//{
//	GLfloat eye[3] = { 3.f, 7.f, 4.f };
//	GLfloat center[3] = { 0.f, 0.f, 0.f };
//	GLfloat up[3] = { 0.f, 1.f, 0.f };
//
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//	//glViewport(0, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
//	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
//
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	//glOrtho(-4.f, 4.f, -4.f, 4.f, 0.5f, 20.f);
//	SDL_TR_Perspective(60.f, 1.f, eye[2] + 0.25f, 20.f);
//
//	gluLookAt(eye[0], eye[1], eye[2], center[0], center[1], center[2], up[0], up[1], up[2]);
//
//	glRotatef(2, 0.25f, 1.f, 0.f);
//
//	glNormal3f(0.f, 0.f, 0.f);
//	glColor3f(0.8f, 0.8f, 0.8f);
//
//	glBegin(GL_POLYGON);
//	glVertex3f(0.f, 4.f, -2.f);
//	glVertex3f(0.f, 0.f, -2.f);
//	glEnd();
//
//
//	//Example1();
//	//Example2();
//	//Example3();
//	//Example4();
//}
