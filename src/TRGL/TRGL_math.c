#include "TRGL_math.h"
#include <stdio.h>


void empty_matrix(float *M, int length)
{
  //for (int i=0;i<length;++i)
    //M[i]=0;
}

/* Es esto una solución coherente? */
void multiply_matrix_3x3_1x3(float M1[9], float M2[3], float RET[3])
{
  RET[0] = M1[0]*M2[0] + M1[1]*M2[1] + M1[2]*M2[2];
  RET[1] = M1[3]*M2[0] + M1[4]*M2[1] + M1[5]*M2[2];
  RET[2] = M1[6]*M2[0] + M1[7]*M2[1] + M1[8]*M2[2];
}

void multiply_matrix_4x4_1x4(const float M1[16], const float M2[16], float MR[16])
{

  for (unsigned int i = 0; i < 16; i += 4)
    for (unsigned int j = 0; j < 4; ++j)
      MR[i + j] = (M2[i + 0] * M1[j +  0])
	+ (M2[i + 1] * M1[j +  4])
	+ (M2[i + 2] * M1[j +  8])
	+ (M2[i + 3] * M1[j + 12]);
}

void print_matrix4x4(float *m)
{
 for (unsigned int i = 0; i < 16; ++i)
    {
      printf("%f ", m[i]);
      if (i  == 3 || i==7 || i==11 || i==15)
	printf("\n");
      if (i == 15)
	printf("\n");
    }
}

void copy_matrix4x4f(float matrix_a[16], float matrix_b[16])
{
  for (int i=0; i < 16; ++i)
    matrix_b[i]=matrix_a[i];
}
