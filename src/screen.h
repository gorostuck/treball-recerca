#ifndef SCREEN_H_INCLUDED
#define SCREEN_H_INCLUDED

#define DEFAULT_MAX_SCREEN_X 512
#define DEFAULT_MAX_SCREEN_Y 512

int  screen_start(void);
int  screen_end(void);

void screen_update_size(void);
void screen_update(void);

void screen_change_color(int r, int g, int b, int a);

void screen_draw_full(void);
void screen_draw_point(int x, int y);
void screen_draw_line(int begin_x, int begin_y,
			int end_x, int end_y);

void screen_start_gl(void);
int  screen_set_viewport(int width, int height);
void screen_display_render(void);


#endif /* SCREEN_H_INCLUDED */


