#include "platform.h"
#include <cstdint>
#include <cstring>

uint32_t buffer_a[800 * 640];
uint32_t buffer_b[800 * 640];
uint32_t *frontbuffer;
uint32_t *backbuffer;

void init_platform(void) {
  memset(buffer_a, 0, sizeof(buffer_a));
  memset(buffer_b, 0, sizeof(buffer_b));
  frontbuffer = buffer_a;
  backbuffer = buffer_b;
}

void destroy_platform(void) {}

void platform_begin_frame(void) { memset(backbuffer, 0, sizeof(buffer_a)); }

void platform_end_frame(void) {
  uint32_t *temp = 0;
  temp = backbuffer;
  backbuffer = frontbuffer;
  frontbuffer = temp;
}

void platform_poll_events(void) {}
