#include "Renderer.h"

//GLfloat ang3 = 1.f;
void render()
{
  glClear(GL_COLOR_BUFFER_BIT);
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

void gluLookAt(GLdouble eyex, GLdouble eyey, GLdouble eyez,
	       GLdouble centerx, GLdouble centery, GLdouble centerz,
	       GLdouble upx, GLdouble upy, GLdouble upz)
{
  GLfloat forward[4], side[4], up[4];
  GLfloat m[16];

  forward[0] = (GLfloat)(centerx - eyex);
  forward[1] = (GLfloat)(centery - eyey);
  forward[2] = (GLfloat)(centerz - eyez);
  forward[3] = 1.f / sqrtf(forward[0] * forward[0] + forward[1] * forward[1] + forward[2] * forward[2]);
  forward[0] *= forward[3];
  forward[1] *= forward[3];
  forward[2] *= forward[3];

  up[0] = (GLfloat)upx;
  up[1] = (GLfloat)upy;
  up[2] = (GLfloat)upz;

  /* Side = forward x up */
  side[0] = forward[1] * up[2] - forward[2] * up[1];
  side[1] = -forward[0] * up[2] + forward[2] * up[0];
  side[2] = forward[0] * up[1] - forward[1] * up[0];
  side[3] = 1.f / sqrtf(side[0] * side[0] + side[1] * side[1] + side[2] * side[2]);
  side[0] *= side[3];
  side[1] *= side[3];
  side[2] *= side[3];

  /* Recompute up as: up = side x forward */
  up[0] = side[1] * forward[2] - side[2] * forward[1];
  up[1] = -side[0] * forward[2] + side[2] * forward[0];
  up[2] = side[0] * forward[1] - side[1] * forward[0];
  up[3] = 1.f / sqrtf(up[0] * up[0] + up[1] * up[1] + up[2] * up[2]);
  up[0] *= up[3];
  up[1] *= up[3];
  up[2] *= up[3];

  m[0] = side[0];			m[1] = side[1];			m[2] = side[2];			 m[3] = 0.f;
  m[4] = up[0];				m[5] = up[1];				m[6] = up[2];				 m[7] = 0.f;
  m[8] = -forward[0]; m[9] = -forward[1]; m[10] = -forward[2]; m[11] = 0.f;
  m[12] = 0.f;				m[13] = 0.f;				m[14] = 0.f;				 m[15] = 1.f;

  glMultMatrixf(m);
  glTranslatef((GLfloat)-eyex, (GLfloat)-eyey, (GLfloat)-eyez);
}

void gluPerspective(GLfloat fovY, GLfloat aspect, GLfloat front, GLfloat back)
{
  GLfloat tangent = tanf(fovY / 2.f * DEG2RAD); // tangent of half fovY
  GLfloat height = front * tangent;         // half height of near plane
  GLfloat width = height * aspect;          // half width of near plane

  glFrustum(-width, width, -height, height, front, back);
}

