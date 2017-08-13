#include "Scanner.h"

#include <stdio.h>


// Definido en List.c
extern struct List *firstList, *currentList;

// Definido en Stack.h
extern const GLfloat Identity[16];

// Valores definidos en Execute.c
extern const size_t sizeof4GLuint;
extern const size_t sizeof4GLfloat;
extern const size_t sizeof16GLfloat;

/*
 * Miscellaneous Functions. SDL_opengl.h
 */

GLAPI void GLAPIENTRY glMatrixMode(GLenum flags)
{
  CreateNode(&(currentList->currentNode), flags);
}

GLAPI void GLAPIENTRY glGetFloatv(GLenum pname, GLfloat *params)
{
  switch (pname)
    {
    case GL_MODELVIEW_MATRIX:
      memcpy(params, currentStack->Model, sizeof16GLfloat);
    default:
      break;
    }
}

/*
 * Display Lists
 */

GLAPI GLboolean GLAPIENTRY glIsList(GLuint list);

GLAPI void GLAPIENTRY glDeleteLists(GLuint list, GLsizei range)
{
  GLuint i;

  for (i = list; i < list + range; i++)
    FreeList( i );
}

GLAPI GLuint GLAPIENTRY glGenLists(GLsizei range)
{
  return CreateLists(range);
}

GLAPI void GLAPIENTRY glNewList(GLuint list, GLenum mode)
{
  struct List *tempList = pointerList(list);

  if (mode == GL_COMPILE_AND_EXECUTE) {
    CreateNode(&(currentList->currentNode), BEGINLIST);
    currentList->currentNode->nextList = tempList;
  }

  currentList = tempList;

  currentList->currentNode = currentList->firstNode;
}

GLAPI void GLAPIENTRY glEndList(void)
{
  CreateNode(&(currentList->currentNode), ENDLIST);

  currentList = firstList;
}

GLAPI void GLAPIENTRY glCallList(GLuint list)
{
  struct List *tempList;

  for (tempList = firstList->Next; tempList->Index = list || tempList == NULL; tempList = tempList->Next);

  if (tempList == NULL)
    printf("Hay un error en CallList %i", list);

  CreateNode(&(currentList->currentNode), LIST);
  currentList->currentNode->nextList = tempList;
}

GLAPI void GLAPIENTRY glCallLists(GLsizei n, GLenum type,	const GLvoid *lists);

GLAPI void GLAPIENTRY glListBase(GLuint base);

/*
 * Drawing Functions. SDL_opengl.h
 */

GLAPI void GLAPIENTRY glBegin(GLenum mode)
{
  CreateNode(&(currentList->currentNode), mode);
}
GLAPI void GLAPIENTRY glEnd()
{
  CreateNode(&(currentList->currentNode), END);
}

GLAPI void GLAPIENTRY glClearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
{
  CreateNode(&(currentList->currentNode), CLEARCOLOR);

  GLuint *Color = currentList->currentNode->Color;

  Color[0] = (GLuint)(red * 255);
  Color[1] = (GLuint)(green * 255);
  Color[2] = (GLuint)(blue * 255);
  Color[3] = (GLuint)(alpha * 255);
}
GLAPI void GLAPIENTRY glVertex2d(GLdouble x, GLdouble y);
GLAPI void GLAPIENTRY glVertex2f(GLfloat x, GLfloat y)
{
  CreateNode(&(currentList->currentNode), GL_POINT);

  GLfloat *Point = currentList->currentNode->Point;

  Point[0] = x;
  Point[1] = y;
  Point[2] = 0.f;
  Point[3] = 1.f;
}
GLAPI void GLAPIENTRY glVertex2i(GLint x, GLint y);
GLAPI void GLAPIENTRY glVertex2s(GLshort x, GLshort y);

GLAPI void GLAPIENTRY glVertex3d(GLdouble x, GLdouble y, GLdouble z);
GLAPI void GLAPIENTRY glVertex3f(GLfloat x, GLfloat y, GLfloat z)
{
  CreateNode(&(currentList->currentNode), GL_POINT);

  GLfloat *Point = currentList->currentNode->Point;

  Point[0] = x;
  Point[1] = y;
  Point[2] = z;
  Point[3] = 1.f;
}

GLAPI void GLAPIENTRY glVertex3i(GLint x, GLint y, GLint z);
GLAPI void GLAPIENTRY glVertex3s(GLshort x, GLshort y, GLshort z);

GLAPI void GLAPIENTRY glVertex4d(GLdouble x, GLdouble y, GLdouble z, GLdouble w);
GLAPI void GLAPIENTRY glVertex4f(GLfloat x, GLfloat y, GLfloat z, GLfloat w);
GLAPI void GLAPIENTRY glVertex4i(GLint x, GLint y, GLint z, GLint w);
GLAPI void GLAPIENTRY glVertex4s(GLshort x, GLshort y, GLshort z, GLshort w);

GLAPI void GLAPIENTRY glNormal3b(GLbyte nx, GLbyte ny, GLbyte nz);
GLAPI void GLAPIENTRY glNormal3d(GLdouble nx, GLdouble ny, GLdouble nz);
GLAPI void GLAPIENTRY glNormal3f(GLfloat nx, GLfloat ny, GLfloat nz)
{
  CreateNode(&(currentList->currentNode), NORMAL);

  GLfloat *Normal = currentList->currentNode->Normal;

  Normal[0] = nx;
  Normal[1] = ny;
  Normal[2] = nz;
  Normal[3] = 0.f;
}
GLAPI void GLAPIENTRY glNormal3i(GLint nx, GLint ny, GLint nz);
GLAPI void GLAPIENTRY glNormal3s(GLshort nx, GLshort ny, GLshort nz);

GLAPI void GLAPIENTRY glNormal3bv(const GLbyte *v);
GLAPI void GLAPIENTRY glNormal3dv(const GLdouble *v);
GLAPI void GLAPIENTRY glNormal3fv(const GLfloat *v);
GLAPI void GLAPIENTRY glNormal3iv(const GLint *v);
GLAPI void GLAPIENTRY glNormal3sv(const GLshort *v);

GLAPI void GLAPIENTRY glColor3b(GLbyte red, GLbyte green, GLbyte blue);
GLAPI void GLAPIENTRY glColor3d(GLdouble red, GLdouble green, GLdouble blue);
GLAPI void GLAPIENTRY glColor3f(GLfloat red, GLfloat green, GLfloat blue)
{
  glColor3ui((GLuint)(red * 255), (GLuint)(green * 255), (GLuint)(blue * 255));
}

GLAPI void GLAPIENTRY glColor3i(GLint red, GLint green, GLint blue);
GLAPI void GLAPIENTRY glColor3s(GLshort red, GLshort green, GLshort blue);
GLAPI void GLAPIENTRY glColor3ub(GLubyte red, GLubyte green, GLubyte blue);
GLAPI void GLAPIENTRY glColor3ui(GLuint red, GLuint green, GLuint blue)
{
  CreateNode(&(currentList->currentNode), COLOR);

  GLuint *Color = currentList->currentNode->Color;

  Color[0] = red;
  Color[1] = green;
  Color[2] = blue;
  Color[3] = 255;
}
GLAPI void GLAPIENTRY glColor3us(GLushort red, GLushort green, GLushort blue);

/*
 * Model Functions. SDL_opengl.h
 */

GLAPI void GLAPIENTRY glPushMatrix(void)
{
  CreateNode(&(currentList->currentNode), PUSHMATRIX);
}

GLAPI void GLAPIENTRY glPopMatrix(void)
{
  CreateNode(&(currentList->currentNode), POPMATRIX);
}

GLAPI void GLAPIENTRY glLoadIdentity(void)
{
  CreateNode(&(currentList->currentNode), LOADIDENTITY);
}

GLAPI void GLAPIENTRY glLoadMatrixd(const GLdouble *m);
GLAPI void GLAPIENTRY glLoadMatrixf(const GLfloat *m)
{
  CreateNode(&(currentList->currentNode), LOADMATRIX);

  memcpy(currentList->currentNode->Matrix, m, sizeof16GLfloat);
}

GLAPI void GLAPIENTRY glMultMatrixd(const GLdouble *m);
GLAPI void GLAPIENTRY glMultMatrixf(const GLfloat *m)
{
  CreateNode(&(currentList->currentNode), MODEL);

  memcpy(currentList->currentNode->Matrix, m, sizeof16GLfloat);
}

GLAPI void GLAPIENTRY glRotated(GLdouble angle, GLdouble x, GLdouble y, GLdouble z);
GLAPI void GLAPIENTRY glRotatef(GLfloat angle, GLfloat x, GLfloat y, GLfloat z)
{
  CreateNode(&(currentList->currentNode), MODEL);

  GLfloat *Matrix = currentList->currentNode->Matrix;

  angle *= DEG2RAD;

  GLfloat sina = sinf(angle), cosa = cosf(angle);

  GLfloat d = sqrtf(x*x + y*y + z*z);
  x /= d; y /= d; z /= d;

  Matrix[0] = cosa + x*x*(1 - cosa);   Matrix[1] = x*y*(1 - cosa) - z*sina; Matrix[2] = x*z*(1 - cosa) + y*sina; Matrix[3] = 0.f;
  Matrix[4] = y*x*(1 - cosa) + z*sina; Matrix[5] = cosa + y*y*(1 - cosa);   Matrix[6] = y*z*(1 - cosa) - x*sina; Matrix[7] = 0.f;
  Matrix[8] = z*x*(1 - cosa) - y*sina; Matrix[9] = z*y*(1 - cosa) + x*sina; Matrix[10] = cosa + z*z*(1 - cosa);  Matrix[11] = 0.f;
  Matrix[12] = 0.f;										Matrix[13] = 0.f;										Matrix[14] = 0.f;										Matrix[15] = 1.f;
}

GLAPI void GLAPIENTRY glScaled(GLdouble x, GLdouble y, GLdouble z);
GLAPI void GLAPIENTRY glScalef(GLfloat x, GLfloat y, GLfloat z)
{
  CreateNode(&(currentList->currentNode), MODEL);

  GLfloat *Matrix = currentList->currentNode->Matrix;

  memcpy(Matrix, Identity, sizeof16GLfloat);
  Matrix[0] = x;
  Matrix[5] = y;
  Matrix[10] = z;
}

GLAPI void GLAPIENTRY glTranslated(GLdouble x, GLdouble y, GLdouble z);
GLAPI void GLAPIENTRY glTranslatef(GLfloat x, GLfloat y, GLfloat z)
{
  CreateNode(&(currentList->currentNode), MODEL);

  GLfloat *Matrix = currentList->currentNode->Matrix;

  memcpy(Matrix, Identity, sizeof16GLfloat); // Matriz para cálculos intermedios
  Matrix[3] = x;
  Matrix[7] = y;
  Matrix[11] = z;
}

/*
 * View Functions. SDL_opengl.h
 */

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


/*
 * Projection. SDL_opengl.h
 */

GLAPI void GLAPIENTRY glOrtho(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble near_val, GLdouble far_val)
{
  CreateNode(&(currentList->currentNode), ORTHO);

  GLfloat *Matrix = currentList->currentNode->Matrix;

  Matrix[0] = (GLfloat)(2. / (right - left));	Matrix[1] = 0.f;			Matrix[2] = 0.f;				 Matrix[3] = (GLfloat)(-(right + left) / (right - left));
  Matrix[4] = 0.f;		Matrix[5] = (GLfloat)(2. / (top - bottom));		Matrix[6] = 0.f;				 Matrix[7] = (GLfloat)(-(top + bottom) / (top - bottom));
  Matrix[8] = 0.f;		Matrix[9] = 0.f;		Matrix[10] = (GLfloat)(-2. / (far_val - near_val)); Matrix[11] = (GLfloat)(-(far_val + near_val) / (far_val - near_val));
  Matrix[12] = 0.f;	Matrix[13] = 0.f;															Matrix[14] = 0.f;			 Matrix[15] = 1.f;
}

GLAPI void GLAPIENTRY glFrustum(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble near_val, GLdouble far_val)
{
  CreateNode(&(currentList->currentNode), FRUSTUM);

  GLfloat *Matrix = currentList->currentNode->Matrix;

  Matrix[0] = (GLfloat)(2. * near_val / (right - left)); Matrix[1] = 0.f;			Matrix[2] = (GLfloat)((right + left) / (right - left));	Matrix[3] = 0.f;
  Matrix[4] = 0.f;			Matrix[5] = (GLfloat)(2. * near_val / (top - bottom)); Matrix[6] = (GLfloat)((top + bottom) / (top - bottom));	Matrix[7] = 0.f;
  Matrix[8] = 0.f;			Matrix[9] = 0.f;				Matrix[10] = (GLfloat)((near_val + far_val) / (near_val - far_val)); Matrix[11] = (GLfloat)(2. * near_val*far_val / (near_val - far_val));
  Matrix[12] = 0.f;		Matrix[13] = 0.f;																			Matrix[14] = -1.f;																				Matrix[15] = 0.f;
}

//GLAPI void GLAPIENTRY glFrustum(GLdouble l, GLdouble r, GLdouble b, GLdouble t, GLdouble n, GLdouble f)
//{
//    int i;
//    for(i=0;i<16;i++)
//      PR[i]=0.f;
//    PR[0]  = 2 * n / (r - l);
//    PR[5]  = 2 * n / (t - b);
//    PR[8]  = (r + l) / (r - l);
//    PR[9]  = (t + b) / (t - b);
//    PR[10] = -(f + n) / (f - n);
//    PR[11] = -1;
//    PR[14] = -(2 * f * n) / (f - n);
//    PR[15] = 0;
//}

void SDL_TR_Perspective(GLfloat fovY, GLfloat aspect, GLfloat front, GLfloat back)
{
  GLfloat tangent = tanf(fovY / 2.f * DEG2RAD); // tangent of half fovY
  GLfloat height = front * tangent;         // half height of near plane
  GLfloat width = height * aspect;          // half width of near plane

  glFrustum(-width, width, -height, height, front, back);
}


/*
 * Viewport. SDL_opengl.h
 */


GLAPI void GLAPIENTRY glViewport(GLint x, GLint y, GLsizei width, GLsizei height)
{
  CreateNode(&(currentList->currentNode), VIEWPORT);

  GLfloat *Matrix = currentList->currentNode->Matrix;

  memcpy(Matrix, Identity, sizeof16GLfloat); // Matriz para cálculos intermedios
  Matrix[0] = (GLfloat)width / 2.f;	 Matrix[3] = (GLfloat)x + (GLfloat)width / 2.f;
  Matrix[5] = -(GLfloat)height / 2.f; Matrix[7] = (GLfloat)y + (GLfloat)height / 2.f;

  //VP[0] = width / 2.; VP[1] = 0.f;					VP[2] = 0.f;  VP[3] = x + width / 2.;
  //VP[4] = 0.f;				VP[5] = -height / 2.; VP[6] = 0.f;  VP[7] = y + height / 2.;
  //VP[8] = 0.f;				VP[9] = 0.f;					VP[10] = 1.f; VP[11] = 0.f;
  //VP[12] = 0.f;			  VP[13] = 0.f;					VP[14] = 0.f; VP[15] = 1.f;
}
