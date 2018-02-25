/* En teoría este archivo tiene que contener las funciones de 
   librería gráfica que existen ahora mismo */

#define DEG2RAD 0.01745329251f // PI / 180
#define RAD2DEG 57.2957795131f // 180 / PI

/* Funciones que no tiene OpenGL */

/* void SDL_TR_Perspective(GLfloat fovY, GLfloat aspect, GLfloat front, GLfloat back); */

/* void gluLookAt(GLdouble eyex, GLdouble eyey, GLdouble eyez, */
/* 	       GLdouble centerx, GLdouble centery, GLdouble centerz, */
/* 	       GLdouble upx, GLdouble upy, GLdouble upz); */

GLboolean SDL_TR_CreateRenderer(SDL_Window *gWindow);

void SDL_TR_Quit();
