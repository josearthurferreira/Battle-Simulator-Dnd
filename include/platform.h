#ifndef INCLUDE_PLATFORM_H_
#define INCLUDE_PLATFORM_H_

void init_platform(void);
void destroy_platform(void);
void platform_poll_events(void);
void handle_events_backend(void);
void platform_begin_frame(void);
void platform_end_frame(void);

#endif // INCLUDE_PLATFORM_H_
