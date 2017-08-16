#include "Objects.h"
#include <math.h>

void Vector(GLfloat size)
{
  glColor3f(1.f, 0.f, 0.f);
  glBegin(GL_LINES);
  glVertex3f(0.f, 0.f, 0.f);
  glVertex3f(0.f, 0.f, size);
  glEnd();
  glBegin(GL_TRIANGLES);
  glVertex3f(0.f, 0.f, size);
  glVertex3f(-0.05f * size, 0.f, 0.8f * size);
  glVertex3f(0.05f * size, 0.f, 0.8f * size);
  glEnd();
}

void Vector2(GLfloat x, GLfloat y, GLfloat z)
{
  GLfloat size = sqrtf(x * x + y * y + z * z);
  x /= size; y /= size; z /= size;

  glColor3f(1.f, 0.f, 0.f);
  glBegin(GL_LINES);
  glVertex3f(0.f, 0.f, 0.f);
  glVertex3f(x, y, z);
  glEnd();
  glBegin(GL_TRIANGLES);
  glVertex3f(x, y, z);
  glVertex3f(0.8f * x + 0.05f, 0.8f * y, 0.8f * z);
  glVertex3f(0.8f * x - 0.05f, 0.8f * y, 0.8f * z);
  glEnd();
}

void AxisPlane(void)
{
  GLfloat i;

  // Plano x = 0 Negro
  glNormal3f(0.f, 0.f, 0.f);
  glColor3f(0.8f, 0.8f, 0.8f);
  for (i = 0; i <= 4; i += 1.f)
    {
      glBegin(GL_LINE_LOOP);
      glVertex3f(0.f, 4.f, i);
      glVertex3f(0.f, 0.f, i);
      glEnd();

      glBegin(GL_LINE_LOOP);
      glVertex3f(0.f, i, 4.f);
      glVertex3f(0.f, i, 0.f);
      glEnd();
    }
  // Plano y = 0. Gris
  glNormal3f(0.f, 0.f, 0.f);
  glColor3f(0.5f, 0.5f, 0.5f);
  for (i = 0; i <= 4; i += 1.f)
    {
      glBegin(GL_LINE_LOOP);
      glVertex3f(4.f, 0.f, i);
      glVertex3f(0.f, 0.f, i);
      glEnd();

      glBegin(GL_LINE_LOOP);
      glVertex3f(i, 0.f, 4.f);
      glVertex3f(i, 0.f, 0.f);
      glEnd();
    }
  //Plano z = 0. Casi blanco
  glColor3f(0.2f, 0.2f, 0.2f);
  glNormal3f(0.f, 0.f, 0.f);
  for (i = 0; i <= 4; i += 1.f)
    {
      glBegin(GL_LINE_LOOP);
      glVertex3f(i, 4.f, 0.f);
      glVertex3f(i, 0.f, 0.f);
      glEnd();

      glBegin(GL_LINE_LOOP);
      glVertex3f(4.f, i, 0.f);
      glVertex3f(0.f, i, 0.f);
      glEnd();
    }
}

void Cubo(GLfloat s)
{
  GLfloat s1 = s * 0.975f;
  // LADO DELANTERO: lado rojo
  glColor3f(1.0, 0.0, 0.0);
  glNormal3f(0.f, 0.f, 1.f);
  glBegin(GL_LINE_LOOP);
  glVertex3f(s1, -s1, s); 
  glVertex3f(s1, s1, s);  
  glVertex3f(-s1, s1, s); 
  glVertex3f(-s1, -s1, s);
  glEnd();

  // LADO TRASERO: lado blanco
  glColor3f(1.0, 1.0, 1.0);
  glNormal3f(0.f, 0.f, -1.f);
  glBegin(GL_LINE_LOOP);
  glVertex3f(s1, -s1, -s);
  glVertex3f(s1, s1, -s);
  glVertex3f(-s1, s1, -s);
  glVertex3f(-s1, -s1, -s);
  glEnd();

  // LADO DERECHO: lado morado
  glColor3f(1.0, 0.0, 1.0);
  glNormal3f(1.f, 0.f, 0.f);
  glBegin(GL_LINE_LOOP);
  glVertex3f(s, -s1, -s1);
  glVertex3f(s, s1, -s1);
  glVertex3f(s, s1, s1);
  glVertex3f(s, -s1, s1);
  glEnd();

  // LADO IZQUIERDO: lado verde
  glColor3f(0.0, 1.0, 0.0);
  glNormal3f(-1.f, 0.f, 0.f);
  glBegin(GL_LINE_LOOP);
  glVertex3f(-s, -s1, s1);
  glVertex3f(-s, s1, s1);
  glVertex3f(-s, s1, -s1);
  glVertex3f(-s, -s1, -s1);
  glEnd();

  // LADO SUPERIOR: lado azul
  glColor3f(0.0, 0.0, 1.0);
  glNormal3f(0.f, 1.f, 0.f);
  glBegin(GL_LINE_LOOP);
  glVertex3f(s1, s, s1);
  glVertex3f(s1, s, -s1);
  glVertex3f(-s1, s, -s1);
  glVertex3f(-s1, s, s1);
  glEnd();

  // LADO INFERIOR: lado 
  glColor3f(1.0, 1.0, 0.0);
  glNormal3f(0.f, -1.f, 0.f);
  glBegin(GL_LINE_LOOP);
  glVertex3f(s1, -s, -s1);
  glVertex3f(s1, -s, s1);
  glVertex3f(-s1, -s, s1);
  glVertex3f(-s1, -s, -s1);
  glEnd();
}

void Esfera(void)
{
  //int i = 0;
  //int j = 0;
  float radio = 0.5f;
  float teta, teta2;
  float phi, phi2;
  //    float porcentajex=0;
  //    float porcentajey=1;

  float ResolucionEsfera = 20.f;
  float FinalPhi = (GLfloat)(2 * PI), FinalTeta = (GLfloat)(2 * PI);

  //   float incrementox = 1.f / (2.f * ResolucionEsfera); //1/20 NO USADO
  //  float incrementoy = -1.f / ResolucionEsfera; //1/10         NO USADO
  float increRad = (float)PI / ResolucionEsfera;
  float Vertice1x, Vertice1y, Vertice1z;
  float Vertice2x, Vertice2y, Vertice2z;
  float Vertice3x, Vertice3y, Vertice3z;
  float Vertice4x, Vertice4y, Vertice4z;
  //-----------\/---------Construcción de la esfera poco a poco---------------
  if (FinalPhi < 2 * PI) FinalPhi += increRad / 50.f;/*FinalPhi=2*PI;*/
  if (FinalTeta < PI) FinalTeta += increRad / 100.f;/*FinalTeta=(float)PI;*/
  //-----------/\---------Construcción de la esfera poco a poco---------------
  for (teta = 0.f, teta2 = increRad; teta<FinalTeta; teta += increRad, teta2 += increRad)
    {
      for (phi = 0.f, phi2 = increRad; phi<FinalPhi; phi += increRad, phi2 += increRad)
	{
	  //VERTICE 1
	  Vertice1z = radio*sinf(teta)*cosf(phi);
	  Vertice1x = radio*sinf(teta)*sinf(phi);
	  Vertice1y = radio*cosf(teta);
	  //VERTICE 2
	  Vertice2z = radio*sinf(teta2)*cosf(phi);
	  Vertice2x = radio*sinf(teta2)*sinf(phi);
	  Vertice2y = radio*cosf(teta2);
	  //VERTICE 3
	  Vertice3z = radio*sinf(teta2)*cosf(phi2);
	  Vertice3x = radio*sinf(teta2)*sinf(phi2);
	  //Vertice3y = radio*cosf(teta + increRad);
	  Vertice3y = Vertice2y;// radio*cosf(teta + increRad);
	  //VERTICE 4
	  Vertice4z = radio*sinf(teta)*cosf(phi2);
	  Vertice4x = radio*sinf(teta)*sinf(phi2);
	  //Vertice4y = radio*cosf(teta);
	  Vertice4y = Vertice1y; // radio*cosf(teta);

	  glNormal3f(sinf(teta)*sinf(phi), cosf(teta), sinf(teta)*cosf(phi));
	  //glNormal3f(1.5f*sinf(teta)*sinf(phi), 1.5f*cosf(teta), 1.5f*sinf(teta)*cosf(phi));
	  //

	  glBegin(GL_LINE_LOOP);
	  glVertex3f(Vertice1x, Vertice1y, Vertice1z);
	  glVertex3f(Vertice2x, Vertice2y, Vertice2z);
	  glVertex3f(Vertice3x, Vertice3y, Vertice3z);
	  glVertex3f(Vertice4x, Vertice4y, Vertice4z);
	  glEnd();
	  //          glBegin(GL_TRIANGLES);
	  //          //TRIANGULO 1
	  ////glTexCoord2f(porcentajex, porcentajey);
	  //            glVertex3f(Vertice1x, Vertice1y,Vertice1z);
	  ////glTexCoord2f(porcentajex,porcentajey+incrementoy);
	  //            glVertex3f(Vertice2x, Vertice2y,Vertice2z);
	  ////glTexCoord2f(porcentajex+incrementox,porcentajey+incrementoy);
	  //            glVertex3f(Vertice3x,Vertice3y,Vertice3z);
	  //            //TRIANGULO 2
	  ////glTexCoord2f(porcentajex, porcentajey);
	  //            glVertex3f(Vertice1x, Vertice1y,Vertice1z);
	  ////glTexCoord2f(porcentajex+incrementox,porcentajey+incrementoy);
	  //            glVertex3f(Vertice3x, Vertice3y,Vertice3z);
	  ////glTexCoord2f(porcentajex+incrementox,porcentajey);
	  //            glVertex3f(Vertice4x, Vertice4y,Vertice4z);

	  //          glEnd();
	}
    }
  //for (teta = 0; teta<FinalTeta; teta += increRad)
  //{
  //	for (phi = 0; phi<FinalPhi; phi += increRad)
  //	{
  //		//VERTICE 1
  //		Vertice1z = radio*sinf(teta)*cosf(phi);
  //		Vertice1x = radio*sinf(teta)*sinf(phi);
  //		Vertice1y = radio*cosf(teta);
  //		//VERTICE 2
  //		Vertice2z = radio*sinf(teta + increRad)*cosf(phi);
  //		Vertice2x = radio*sinf(teta + increRad)*sinf(phi);
  //		Vertice2y = radio*cosf(teta + increRad);
  //		//VERTICE 3
  //		Vertice3z = radio*sinf(teta + increRad)*cosf(phi + increRad);
  //		Vertice3x = radio*sinf(teta + increRad)*sinf(phi + increRad);
  //		//Vertice3y = radio*cosf(teta + increRad);
  //		Vertice3y = Vertice2y;// radio*cosf(teta + increRad);
  //													//VERTICE 4
  //		Vertice4z = radio*sinf(teta)*cosf(phi + increRad);
  //		Vertice4x = radio*sinf(teta)*sinf(phi + increRad);
  //		//Vertice4y = radio*cosf(teta);
  //		Vertice4y = Vertice1y; // radio*cosf(teta);

  //		glNormal3f(1.5f*sinf(teta)*sinf(phi), 1.5f*cosf(teta), 1.5f*sinf(teta)*cosf(phi));
  //		//

  //		glBegin(GL_QUADS);
  //		glVertex3f(Vertice1x, Vertice1y, Vertice1z);
  //		glVertex3f(Vertice2x, Vertice2y, Vertice2z);
  //		glVertex3f(Vertice3x, Vertice3y, Vertice3z);
  //		glVertex3f(Vertice4x, Vertice4y, Vertice4z);
  //		glEnd();
  //		//          glBegin(GL_TRIANGLES);
  //		//          //TRIANGULO 1
  //		////glTexCoord2f(porcentajex, porcentajey);
  //		//            glVertex3f(Vertice1x, Vertice1y,Vertice1z);
  //		////glTexCoord2f(porcentajex,porcentajey+incrementoy);
  //		//            glVertex3f(Vertice2x, Vertice2y,Vertice2z);
  //		////glTexCoord2f(porcentajex+incrementox,porcentajey+incrementoy);
  //		//            glVertex3f(Vertice3x,Vertice3y,Vertice3z);
  //		//            //TRIANGULO 2
  //		////glTexCoord2f(porcentajex, porcentajey);
  //		//            glVertex3f(Vertice1x, Vertice1y,Vertice1z);
  //		////glTexCoord2f(porcentajex+incrementox,porcentajey+incrementoy);
  //		//            glVertex3f(Vertice3x, Vertice3y,Vertice3z);
  //		////glTexCoord2f(porcentajex+incrementox,porcentajey);
  //		//            glVertex3f(Vertice4x, Vertice4y,Vertice4z);

  //		//          glEnd();
  //	}
  //}
}

