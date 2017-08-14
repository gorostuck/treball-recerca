#include "main.h"

int main(int argc, char* argv[])
{
  //Start up SDL and create window
  if (!init_window()) {
      printf("Failed to initialize!\n");
  } else {
    //Event handler
    SDL_Event e;
    
    //Enable text input
    SDL_StartTextInput();
    
    //While application is running
    while (!quit) {
	//Handle events on queue
	while (SDL_PollEvent(&e) != 0) {
	    //User requests quit
	    if (e.type == SDL_QUIT) {
		  quit = SDL_TRUE;
		}
	    //Handle keypress with current mouse position
	    else if (e.type == SDL_TEXTINPUT) {
		int x = 0, y = 0;
		SDL_GetMouseState(&x, &y);
		handleKeys(e.text.text[0], x, y);
	    }
	}
	
	//Render quad
	render();
	
	//Update screen
	//SDL_TR_SwapWindow(gWindow);
	
#ifdef TRGL_MODE
	SDL_TR_SwapWindow();
#else
	SDL_GL_SwapWindow(gWindow);
#endif /* TRGL_MODE */
	
	SDL_Delay(20);
    }
    //Disable text input
    SDL_StopTextInput();
  }
  
  //Free resources and close SDL
  close_window();
  return 0;
}
