// code nicked mainly from here:
// http://lazyfoo.net/tutorials/SDL/50_SDL_and_opengl_2/index.php


/* to compile
    ### installation on ubuntu
    # install compiler etc
    sudo apt-get install --yes software-properties-common g++ make
    # install sdl2
    sudo apt-get install --yes libsdl2-dev
    # install opengl
    sudo apt-get install --yes freeglut3-dev
    # compile with
    g++ main.cpp -I /usr/include/SDL2/ -lSDL2  -lGL
    ## installation on mac
    # install xcode with command line tools
    # install sdl2*.dmg, put everything in ~/Library/Frameworks
    # compile with with g++ (or with clang++)
    g++ main.cpp -I ~/Library/Frameworks/SDL2.framework/Headers -I OpenGL -framework SDL2  -F ~/Library/Frameworks -framework OpenGL
*/

#include <SDL2/SDL.h>

#ifdef TRGL_MODE
#include "TRGL/TRGL.h"
#else
#include <SDL2/SDL_opengl.h>
#endif

#include <stdio.h>

#define false 0
#define true  1

//Screen dimension constants
#define SCREEN_WIDTH   640
#define SCREEN_HEIGHT  640


//Main loop flag
int quit = false;
float val = 1.0f;

//Starts up SDL, creates window, and initializes OpenGL
int init_window();

//Initializes matrices and clear color
int initGL();

//Input handler
void handleKeys( unsigned char key, int x, int y );

//Per frame update
void update();

//Renders quad to the screen
void render();

//Frees media and shuts down SDL
void close_window();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//OpenGL context
SDL_GLContext gContext;

//Render flag
int gRenderQuad = true;

int init_window()
{
  //Initialization flag
  int success = true;

  //Initialize SDL
  if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
    printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
    success = false;
  } else {
#ifndef TRGL_MODE
    //Use OpenGL 2.1
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 2 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );

    //Create window
    gWindow = SDL_CreateWindow( "OpenGL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );
    if( gWindow == NULL ) {
      printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
      success = false;
    } else {
      //Create context
      gContext = SDL_GL_CreateContext( gWindow );
      if( gContext == NULL ) {
	printf( "OpenGL context could not be created! SDL Error: %s\n", SDL_GetError() );
	success = false;
      } else {
	//Use Vsync
	if( SDL_GL_SetSwapInterval( 1 ) < 0 ) {
	  printf( "Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError() );
	}
	//Initialize OpenGL
	if( !initGL() ) {
	  printf( "Unable to initialize OpenGL!\n" );
	  success = false;
	}
      }
    }
#else
    gWindow = SDL_CreateWindow("TRGL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL) {
      printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
      success = false;
    }
    else {
      SDL_TR_CreateRenderer(gWindow);
      if (!initGL()) {
	printf("Unable to initialize TRGL!\n");
	success = false;
      }
    }
#endif /* TRGL_MODE */
  }

  return success;
}

int initGL()
{
  
  //Initialize Projection Matrix
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  

  //Initialize Modelview Matrix
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();
  

  //Initialize clear color
  glClearColor( 1.f, 1.f, 1.f, 0.f );
  glClear(GL_COLOR_BUFFER_BIT);
  


  return true;
}

void handleKeys( unsigned char key, int x, int y )
{
  if (key==';') quit = true;

  if (key=='q') glTranslatef(0.01f, 0.0f, 0.0f);
  if (key=='a') glTranslatef(-0.01f, 0.0f, 0.0f);
  if (key=='w') glTranslatef(0.0f, 0.01f, 0.0f);
  if (key=='s') glTranslatef(0.0f, -0.01f, 0.0f);
  if (key=='e') glTranslatef(0.0f, 0.0f, 0.01f);
  if (key=='d') glTranslatef(0.0f, 0.0f, -0.01f);

  if (key=='r') glRotatef(1.f, 1.0f, 0.0f, 0.0f);
  if (key=='f') glRotatef(1.f, -1.0f, 0.0f, 0.0f);
  if (key=='t') glRotatef(1.f, 0.0f, 1.0f, 0.0f);
  if (key=='g') glRotatef(1.f, 0.0f, -1.0f, 0.0f);
  if (key=='y') glRotatef(1.f, 0.0f, 0.0f, 1.0f);
  if (key=='h') glRotatef(1.f, 0.0f, 0.0f, -1.0f);

  

  if (key==' ') glLoadIdentity();
   

}

void update()
{
    //No per frame update needed
}

void render()
{
  //Clear color buffer
  glClear( GL_COLOR_BUFFER_BIT );
    
  //Render quad
  if( gRenderQuad ) {
    //glRotatef(0.14f,0.0f,1.0f,0.0f);    // Rotate The cube around the Y axis
    //glRotatef(0.5f, 0.0f,0.0f,1.0f);

    // glTranslatef(0.1f, 0.0f, 0.0f);
    //glRotatef(1.f, .0f, 0.0f, 1.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin( GL_QUADS );
    
    glVertex3f( -0.25f, -0.25f , 0.25f);
    glVertex3f( 0.25f, -0.25f , 0.25f);
    glVertex3f( 0.25f, 0.25f , 0.25f);
    glVertex3f(-0.25f, 0.25f, 0.25f);

    glVertex3f( -0.25f, -0.25f , 0.0f);
    glVertex3f( 0.25f, -0.25f , 0.0f);
    glVertex3f( 0.25f, 0.25f , 0.0f);
    glVertex3f(-0.25f, 0.25f, 0.0f);

    glVertex3f( -0.25f, -0.25f , 0.25f);
    glVertex3f( 0.25f, -0.25f , 0.25f);
    glVertex3f( 0.25f, -0.25f , 0.0f);
    glVertex3f(-0.25f, -0.25f, 0.0f);

    glVertex3f( -0.25f, 0.25f , 0.25f);
    glVertex3f( 0.25f, 0.25f , 0.25f);
    glVertex3f( 0.25f, 0.25f , 0.0f);
    glVertex3f(-0.25f, 0.25f, 0.0f);

    
    // glVertex2f(-val/2, -val/2); 
    /* glVertex2f(val/2, -val/2); */
    /* glVertex2f(val/2, val/2); */
    /* glVertex2f(-val/2, val/2); */

    /* glVertex2f(-val/3, -val/3); */
    /* glVertex2f(val/3, -val/3); */
    /* glVertex2f(val/3, val/3); */
    /* glVertex2f(-val/3, val/3); */

    /* glVertex2f( -val/3, -val/3 ); */
    /* glVertex2f( val/2, -val/2 ); */
    /* glVertex2f( val/3, val/3 ); */
    /* glVertex2f( -val/2, val/2 ); */

    /* glVertex2f( -val/2, -val/2 ); */
    /* glVertex2f( val/3, -val/3 ); */
    /* glVertex2f( val/2, val/2 ); */
    /* glVertex2f( -val/3, val/3 ); */
    
    glEnd();
    val -= 0.01f;
  }
}

void close_window()
{
    //Destroy window
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;

    //Quit SDL subsystems
    SDL_Quit();
}

 int main( int argc, char* argv[] )
{
  
    //Start up SDL and create window
    if( !init_window() )
    {
        printf( "Failed to initialize!\n" );
    }
    else
    {
      
        //Event handler
        SDL_Event e;

        //Enable text input
        SDL_StartTextInput();

        //While application is running
        while( !quit )
        {
            //Handle events on queue
            while( SDL_PollEvent( &e ) != 0 )
            {
                //User requests quit
                if( e.type == SDL_QUIT )
                {
                    quit = true;
                }
                //Handle keypress with current mouse position
                else if( e.type == SDL_TEXTINPUT )
                {
                    int x = 0, y = 0;
                    SDL_GetMouseState( &x, &y );
                    handleKeys( e.text.text[ 0 ], x, y );
                }
            }

            //Render quad
            render();
	    

            //Update screen
#ifdef TRGL_MODE
	    SDL_TR_SwapWindow(gWindow);
#else
            SDL_GL_SwapWindow( gWindow );
#endif
	    SDL_Delay(5);
        }
        //Disable text input
        SDL_StopTextInput();
      
      
    }

      
    //Free resources and close SDL
    close_window();

  
    return 0;
}


