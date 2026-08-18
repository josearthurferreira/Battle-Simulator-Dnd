#ifndef INCLUDE_PLATFORM_H_
#define INCLUDE_PLATFORM_H_

void init_platform(void);
void destroy_platform(void);
void platform_poll_events(void);
void handle_events_backend(void);
void platform_begin_frame(void);
void platform_end_frame(void);

void draw_square(int x, int y, int w, int h);

class Game;
extern Game *gGame;

#endif // INCLUDE_PLATFORM_H_
