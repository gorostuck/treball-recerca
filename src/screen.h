#ifndef CSCREEN_H
#define CSCREEN_H

#include <SDL2/SDL.h>

#define MAX_SCREEN_X 512
#define MAX_SCREEN_Y 512

class cScreen
{
    public:
        SDL_Window *window;
        SDL_Renderer *renderer;

        cScreen();
        virtual ~cScreen();
        int start_screen(void);
        int end_screen(void);
        void wait_screen(int time);
        void draw_screen();

    protected:
    private:
};

#endif // CSCREEN_H
