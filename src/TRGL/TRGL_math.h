#ifndef TRGL_MATH_H
#define TRGL_MATH_H

void empty_matrix(float *M, int length);

void multiply_matrix_3x3_1x3(float M1[9], float M2[3], float RET[3]);
void multiply_matrix_4x4_1x4(const float M1[16], float M2[16], float MR[16]);
void print_matrix4x4(float *m);


#endif /* TRGL_MATH_H */

