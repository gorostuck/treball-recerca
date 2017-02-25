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
    protected:
    private:
        SDL_Window *window;
        SDL_Renderer *renderer;

        int max_x;
        int max_y;
};

#endif // SCREEN_H_INCLUDED
