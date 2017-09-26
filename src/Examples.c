#include "Examples.h"

#ifdef TRGL_MODE
#include "TRGL/TRGL.h"
#endif /* TRGL_MODE */
#include "Renderer.h"

void Example1(void)
{
  static GLfloat ang2 = 1.f;

  GLfloat eye[3] = { 10.f, 10.f, 10.f };
  GLfloat center[3] = { 0.f, 0.f, 0.f };
  GLfloat up[3] = { 0.f, 1.f, 0.f };

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  //glOrtho(-4.f, 4.f, -4.f, 4.f, 0.5f, 20.f);
  gluPerspective(60.f, (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT, 0.25f, 35.f);
  //SDL_TR_Perspective(60.f, 1.f, eye[2] + 0.25f, 20.f);

  //gluLookAt(eye[0], eye[1], eye[2], center[0], center[1], center[2], up[0], up[1], up[2]);

  //glRotatef(2*ang2, 0.25f, 1.f, 0.f);
  //AxisPlane();

  glTranslatef(0.f, 0.f, -20.0f);
  glRotatef(3 * ang2, 0.25f, 0.5f, 1.f);
  //glTranslatef(1.f, 0.f, 0.f);
  //glRotatef(2 * ang2, 1.f, 0.5f, 0.25f);

  //glTranslatef(1.f, -1.f, -7.f);
  //glRotatef(ang2, 0.f, 1.f, 1.f);
  Cubo(0.75f);
  AxisPlane();
  glScalef(5.f, 5.f, 5.f);
  glColor3f(0.f, 0.f, 0.f);
  Esfera();

  ang2 += 1.f;
}

void Example2(void)
{
  static GLfloat ang3 = 1.f;
  GLfloat eye[3] = { 3.f, 0.f, 0.f };
  GLfloat center[3] = { 0.f, 0.f, 0.f };
  GLfloat up[3] = { 0.f, 1.f, 0.f };

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glViewport(SCREEN_WIDTH / 2, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.f, 2.f, eye[2] + 0.5f, 20.f);
  //glFrustum(-2.f, 2.f, -2.f, 2.f, 0.5f, 20.f);
  //gluLookAt(eye[0], eye[1], eye[2], center[0], center[1], center[2], up[0], up[1], up[2]);

  //AxisPlane();
  glTranslatef(0.15f, 0.15f, -3.9f);
  //glRotatef(25.f, 0.f, 1.f, 0.f);
  glRotatef(-ang3, 0.5f, 0.25f, 1.f);

  glScalef(1.f, 1.5f, 2.f);
  Cubo(0.5f);

  ++ang3;// += 1.f;
}

void Example3(void)
{
  static GLfloat ang4 = 1.f;
  GLfloat eye[3] = { 3.f, 9.5f, 4.f };
  GLfloat center[3] = { 0.f, 0.f, 0.f };
  GLfloat up[3] = { 0.f, 1.f, 0.f };

  glColor3f(0.0f, 0.5f, 0.0f);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  //glViewport(0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2);
  glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  //SDL_TR_Perspective(60.f, 2.f, 0.5f, 20.f);
  //glFrustum(-2.f, 2.f, -2.f, 2.f, 0.5f, 20.f);
  //glOrtho(-2.f, 2.f, -2.f, 2.f, 0.5f, 20.f);
  gluPerspective(60.f, 1.f, eye[2] + 0.25f, 20.f);

  gluLookAt(eye[0], eye[1], eye[2], center[0], center[1], center[2], up[0], up[1], up[2]);

  glRotatef(2 * ang4, 0.25f, 1.f, 0.f);
  AxisPlane();

  glTranslatef(2.f, 2.f, 2.0f);
  glRotatef(3 * ang4, 0.25f, 0.5f, 1.f);
  glTranslatef(1.f, 0.f, 0.f);
  glRotatef(5 * ang4, 1.f, -0.5f, 0.25f);
  glScalef(3.f, 3.f, 3.f);

  Esfera();

  ang4 += 1.f;
}

void Example4(void)
{
  static GLfloat ang4 = 1.f;
  GLfloat eye[3] = { 0.f, 4.f, 9.f };
  GLfloat center[3] = { 0.f, 0.f, 0.f };
  GLfloat up[3] = { 0.f, 1.f, 0.f };

  glColor3f(0.0f, 0.5f, 0.0f);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  //glFrustum(-2.f, 2.f, -2.f, 2.f, 0.5f, 20.f);
  //glOrtho(-6.f, 6.f, -6.f, 6.f, 0.5f, 20.f);
  gluPerspective(60.f, 1.f, eye[2] + 0.25f, 20.f);

  gluLookAt(eye[0], eye[1], eye[2], center[0], center[1], center[2], up[0], up[1], up[2]);

  glRotatef(2 * ang4, 0.f, 1.f, 0.f);
  AxisPlane();


  ///////////////////
  //GLuint lista = glGenLists(1); // Reserva espacio para una lista.

  ////Compilación de una Lista
  //	glNewList(lista, GL_COMPILE);
  ///* DIBUJAR PRIMITIVAS */
  //glEndList();

  ////Llamada y Eliminación de Listas

  //	glCallList(lista);         // Dibuja la lista compilada

  //glDeleteLists(lista, 1);   // Borra una lista
  //////////////////////
  Vector(1.f);
  Vector2(-1.f, -1.f, -1.f);

  glTranslatef(2.f, 2.f, 2.f);
  glRotatef(3 * ang4, 0.25f, 0.5f, 1.f);
  glTranslatef(1.f, 0.f, 0.f);
  glRotatef(5 * ang4, 1.f, -0.5f, 0.25f);

  //GLfloat mat[16];
  //glGetFloatv(GL_MODELVIEW_MATRIX, mat);

  glScalef(3.f, 3.f, 3.f);

  Esfera();

  //glLoadMatrixf(mat);
  //glScalef(1.f, 1.f, 1.f);
  Cubo(0.5f);


  ang4 += 1.f;
}

