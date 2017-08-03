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

void multiply_matrix_4x4_1x4(const float M1[16], float M2[4], float RET[4])
{
  RET[0] = M1[0]*M2[0]  + M1[1]*M2[1]  + M1[2]*M2[2]  + M1[3]*M2[3];
  RET[1] = M1[4]*M2[0]  + M1[5]*M2[1]  + M1[6]*M2[2]  + M1[7]*M2[3];
  RET[2] = M1[8]*M2[0]  + M1[9]*M2[1]  + M1[10]*M2[2] + M1[11]*M2[3];
  RET[3] = M1[12]*M2[0] + M1[13]*M2[1] + M1[14]*M2[2] + M1[15]*M2[3];

  //      printf("%f * %f + %f * %f + %f * %f + %f * %f = %f\n",
  //	 M1[0], M2[0], M1[1], M2[1], M1[2], M2[2], M1[3], M2[3], RET[0]);

}
