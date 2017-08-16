#include "Matrix.h"

#include <stdlib.h>
#include <stdio.h>

// Valores definidos en Execute.c
extern const size_t sizeof4GLuint;
extern const size_t sizeof4GLfloat;
extern const size_t sizeof16GLfloat;

//A * B = C
void Multiplicacion4x4(GLfloat *A, GLfloat *B, GLfloat *C)
{
  GLfloat tempf[16]; // Matriz para cálculos intermedios
  GLubyte i, j;

  for (i = 0; i < 4; ++i)
    for (j = 0; j < 4; ++j)
      tempf[4 * i + j] = A[4 * i] * B[j] +
	A[4 * i + 1] * B[j + 4] +
	A[4 * i + 2] * B[j + 8] +
	A[4 * i + 3] * B[j + 12];
  memcpy(C, tempf, sizeof16GLfloat);
}

//A * B * C = D
void Multiplicacion24x4(GLfloat *A, GLfloat *B, GLfloat *C, GLfloat *D)
{
  GLfloat tempf[16]; // Matriz para cálculos intermedios
  GLubyte i, j;
  for (i = 0; i < 4; ++i)
    for (j = 0; j < 4; ++j)
      tempf[4 * i + j] = B[4 * i] * C[j] +
	B[4 * i + 1] * C[j + 4] +
	B[4 * i + 2] * C[j + 8] +
	B[4 * i + 3] * C[j + 12];
  for (i = 0; i < 4; ++i)
    for (j = 0; j < 4; ++j)
      D[4 * i + j] = A[4 * i] * tempf[j] +
	A[4 * i + 1] * tempf[j + 4] +
	A[4 * i + 2] * tempf[j + 8] +
	A[4 * i + 3] * tempf[j + 12];
}

// Cálculo de la inversa de una matriz 4x4 por el método de Gauss (en general cambiar 4 por n, y pasarlo como parámetro
void Inverse4x4(GLfloat *m, GLfloat *mi)
{
  GLfloat matrix[4][8], ratio, a;
  GLubyte i, j, k;

  for (i = 0; i < 4; ++i) {
    for (j = 0; j < 4; ++j) {
      matrix[i][j] = m[4 * i + j];
    }
  }

  for (i = 0; i < 4; ++i) {
    for (j = 4; j < 8; ++j) {
      if (i == (j - 4))
	matrix[i][j] = 1.0;
      else
	matrix[i][j] = 0.0;
    }
  }
  for (i = 0; i < 4; ++i) {
    for (j = 0; j < 4; ++j) {
      if (i != j) {
	ratio = matrix[j][i] / matrix[i][i];
	for (k = 0; k < 2 * 4; k++) {
	  matrix[j][k] -= ratio * matrix[i][k];
	}
      }
    }
  }
  for (i = 0; i < 4; ++i) {
    a = matrix[i][i];
    for (j = 0; j < 8; ++j) {
      matrix[i][j] /= a;
    }
  }
  for (i = 0; i < 4; ++i) {
    for (j = 0; j < 4; ++j) {
      mi[4 * i + j] = matrix[i][4 + j];
    }
  }

}

void MatrixxPoint4x4(GLfloat *Matrix, GLfloat *Point, GLfloat *Point2)
{
  GLfloat tempf[4]; // Matriz para cálculos intermedios
  GLubyte i;

  for (i = 0; i < 4; i++)
    tempf[i] = Matrix[4 * i + 0] * Point[0] +
      Matrix[4 * i + 1] * Point[1] +
      Matrix[4 * i + 2] * Point[2] +
      Matrix[4 * i + 3] * Point[3];
  Point2[0] /= Point2[3];
  Point2[1] /= Point2[3];
  Point2[2] /= Point2[3];
  Point2[3] /= Point2[3];

  memcpy(Point2, tempf, sizeof4GLfloat);
}


void VectorxMatrix4x4(GLfloat *Vector, GLfloat *Matrix, GLfloat *Vector2)
{
  GLubyte i;

  for (i = 0; i < 3; ++i)
    Vector2[i] = Vector[0] * Matrix[i] + Vector[1] * Matrix[4 + i] + Vector[2] * Matrix[8 + i];
}

void Normalize4(GLfloat *Point)
{
  Point[0] /= Point[3];
  Point[1] /= Point[3];
  Point[2] /= Point[3];
  Point[3] /= Point[3];
}

void PrintMatrix4x4(GLfloat *Matrix)
{
  for (GLuint i = 0; i < 16; ++i){
    printf("%f ", Matrix[i]);
    if ( i==3 || i==7 || i==11 || i==15 )
      printf("\n");
    if (i == 15)
      printf("\n");
  }
}



