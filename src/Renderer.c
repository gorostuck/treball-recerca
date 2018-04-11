#include "Renderer.h"

void render(GLint level, GLfloat time)
{
  glClear(GL_COLOR_BUFFER_BIT);
  glClearColor(1.f, 0.5f, 0.25f, 1.f);
  Presentacion(level, time);
}

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

  m[0] = side[0];      m[1] = side[1];	     m[2] = side[2];	  m[3] = 0.f;
  m[4] = up[0];	       m[5] = up[1];	     m[6] = up[2];	  m[7] = 0.f;
  m[8] = -forward[0];  m[9] = -forward[1];   m[10] = -forward[2]; m[11] = 0.f;
  m[12] = 0.f;	       m[13] = 0.f;	     m[14] = 0.f;	  m[15] = 1.f;

  glMultMatrixf(m);
  glTranslatef((GLfloat)-eyex, (GLfloat)-eyey, (GLfloat)-eyez);
}

void gluPerspective(GLfloat fovY, GLfloat aspect, GLfloat front, GLfloat back)
{
  GLfloat tangent = tanf(fovY / 2.f * DEG2RAD); // tangent of half fovY
  GLfloat height = front * tangent;             // half height of near plane
  GLfloat width = height * aspect;              // half width of near plane

  glFrustum(-width, width, -height, height, front, back);
}

