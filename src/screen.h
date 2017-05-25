/* Este archivo contiene las declaraciones sobre diversos
   aspectos de la ventana */
#ifndef SCREEN_H_INCLUDED
#define SCREEN_H_INCLUDED

#include <SDL2/SDL.h>

#define DEFAULT_MAX_SCREEN_X 512
#define DEFAULT_MAX_SCREEN_Y 512

class Screen
{
    public:
        Screen();
        virtual ~Screen();
        int start_screen(void);
        int end_screen(void);
        void wait_screen(int time);
	void draw_screen();
	void update_size();

	void change_color(int r, int g, int b, int a);
	void draw_full();
	void draw_point(int x, int y);
	void draw_line(int begin_x, int begin_y,
		       int end_x, int end_y);
	void update();

	int max_x;
	int max_y;

    protected:
    private:
        SDL_Window *window;
        SDL_Renderer *renderer;

};

#endif // SCREEN_H_INCLUDED
