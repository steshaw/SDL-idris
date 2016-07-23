#ifndef SDL2_H__
#define SDL2_H__

#include <SDL2/SDL.h>
#include <idris_rts.h>

// Start SDL, open a window with dimensions (w, h)
void* startSDL(int w, int h);

// Drawing primitives
void filledRect(void *r_in,
                int x, int y, int w, int h,
                int r, int g, int b, int a);
void flipBuffers(void* r_in);
void filledEllipse(void* r_in,
                   int x, int y, int rx, int ry,
                   int r, int g, int b, int a);
void drawLine(void* r_in,
              int x, int y, int ex, int ey,
              int r, int g, int b, int a);

// Events
void* pollEvent(VM* vm); // builds an Idris value

#endif
