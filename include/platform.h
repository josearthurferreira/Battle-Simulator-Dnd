#ifndef INCLUDE_PLATFORM_H_
#define INCLUDE_PLATFORM_H_

#include "types.h"

void init_platform(void);
void destroy_platform(void);
void platform_poll_events(void);
void handle_events_backend(void);
void platform_begin_frame(void);
void platform_end_frame(void);

void *platform_load_img(const char *path);
void platform_destroy_img(void *data);

void draw_square(int x, int y, int w, int h);
void render_text(int x, int y, const char *text, float size);
void platform_render_sprite(void *data, Vec2f size, Vec2f pos, bool hFLip,
                            bool vFlip, float rot_angle, unsigned frameNum);

class Game;
extern Game *gGame;

#endif // INCLUDE_PLATFORM_H_
