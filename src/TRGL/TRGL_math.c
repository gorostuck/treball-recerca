#include "TRGL_math.h"


void empty_matrix(float *M, int length)
{
  for (int i=0;i<length;++i)
    M[i]=0;
}

/* Es esto una solución coherente? */
void multiply_matrix_3x3_1x3(float M1[9], float M2[3], float RET[3])
{
  RET[0] = M1[0]*M2[0] + M1[1]*M2[1] + M1[2]*M2[2];
  RET[1] = M1[3]*M2[0] + M1[4]*M2[1] + M1[5]*M2[2];
  RET[2] = M1[6]*M2[0] + M1[7]*M2[1] + M1[8]*M2[2];
}
