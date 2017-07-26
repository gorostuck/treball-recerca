#include "TRGL_math.h"

#define R_X 0                       /*    [ Rx  Px  Sx  0 ]   */
#define R_Y 4                       /*    [ Ry  Py  Sy  0 ]   */
#define R_Z 8                       /*    [ Rz  Pz  0   0 ]   */
#define R_W 12                      /*    [ Rw  Pw  0   0 ]   */
#define P_X 1
#define P_Y 5
#define P_Z 9
#define P_W 13
#define S_X 2
#define S_Y 10

void empty_matrixf(float M[16])
{
  for (int i=0;i<16;++i)
    M[i]=0;
}

void multiply_matrixf(float M1[16], float M2[16], float R[16])
{
  R[0] = M1[0]*M2[0] + M1[1]*M2[4] + M1[2]*M2[8] + M1[3]*M2[12];
  // TODO: Terminar esto, pero por el momento puedo utilizar un modelo más sencillo
}

/* Es muy específico, se utiliza sólo para pasar de coordenadas normalizadas a puntos en la pantalla */
void simple_multiply_matrixf(float M1[16], float M2[16])
{
  M1[S_X] = M1[0]*M2[0] + M1[4]*M2[1] + M2[2]; 
  M1[S_Y] = M1[4]*M2[0] + M1[5]*M2[5] + M2[6];
}
