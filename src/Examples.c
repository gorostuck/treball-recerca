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
  gluPerspective(60.f, (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT, 0.25f, 35.f);

  glTranslatef(0.f, 0.f, -20.0f);
  glRotatef(3 * ang2, 0.25f, 0.5f, 1.f);

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
  glTranslatef(0.15f, 0.15f, -3.9f);
  glRotatef(-ang3, 0.5f, 0.25f, 1.f);

  glScalef(1.f, 1.5f, 2.f);
  Cubo(0.5f);

  ++ang3;
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
  glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
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

  gluPerspective(60.f, 1.f, eye[2] + 0.25f, 20.f);

  gluLookAt(eye[0], eye[1], eye[2], center[0], center[1], center[2], up[0], up[1], up[2]);

  glRotatef(2 * ang4, 0.f, 1.f, 0.f);
  AxisPlane();


  Vector2(-1.f, -1.f, -1.f);

  glTranslatef(2.f, 2.f, 2.f);
  glRotatef(3 * ang4, 0.25f, 0.5f, 1.f);
  glTranslatef(1.f, 0.f, 0.f);
  glRotatef(5 * ang4, 1.f, -0.5f, 0.25f);


  glScalef(3.f, 3.f, 3.f);

  Esfera();

  Cubo(0.5f);


  ang4 += 1.f;
}

void Presentacion(GLint level, GLfloat time)
{
  GLfloat eye[3] = { 10.f, 10.f, 10.f };
  GLfloat center[3] = { 0.f, 0.f, 0.f };
  GLfloat up[3] = { 0.f, 1.f, 0.f };

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.f, (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT, 0.25f, 25.f);

  if (level == 0) {
    glTranslatef(0.f, 0.f, -5.f);
    glRotatef(-25.f, 0.f, 1.f, 0.f);
    Cubo0();
  }
  if (level == 1) {
    glTranslatef(0.f, 0.f, -5.f);
    glRotatef(-25.f, 0.f, 1.f, 0.f);
    if (time > 60.f) {
      float ang = 0.5 * (time-60.f);
      if (ang > 25.f) ang = 25.f;
      glRotatef (ang, 0.f, 1.f, 0.f);
    }
    Plano1();
    GLfloat margin = 1.f - 0.02 * time;
    if (margin < 0) margin = 0;
    Cubo1(margin);
  }
  if (level == 2){
    glTranslatef(0.f, 0.f, -5.f);
    Plano2();
  }
  if (level == 3){
    glTranslatef(-2.f, 0.f, -5.f);
    static float factor = 0;
    if (time == 0) factor = 0;
    if (time > 30.f && time < 80.f) factor +=1.f;
    glTranslatef(0.08 * factor, 0.f, 0.f);
    glRotatef(0.9 * factor, 0.f, 0.f, 1.f);
    glScalef(1.f - (0.01 * factor), 1.f - (0.01 * factor), 1.f - (0.01 *factor));
    CuboNegro(0.5f);
  }
  if (level == 4){
    glTranslatef(-2.f, 0.f, -5.f);
    static float factor1 = 0;
    static float factor2 = 0;
    static float factor3 = 0;
    if (time == 0) {
      factor1 = 0;
      factor2 = 0;
      factor3 = 0;
    }
    if (time > 30.f && time < 80.f) factor1 += 1.f;
    if (time > 100.f && time < 150.f) factor2 += 1.f;
    if (time > 180.f && time < 220.f) factor3 += 1.f;
    glTranslatef(0.08 * factor1, 0.f, 0.f);
    glRotatef(0.9 * factor2, 0.f, 0.f, 1.f);
    glScalef(1.f - (0.01 * factor3), 1.f - (0.01 * factor3), 1.f - (0.01 *factor3));
    //    CuboNegro(0.5f);
    Esfera();
  }
}
