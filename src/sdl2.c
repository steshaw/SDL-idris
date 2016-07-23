#include "sdl2.h"
#include <SDL2/SDL2_gfxPrimitives.h>
#include <stdio.h>

SDL_Renderer* idris_sdl2_init(int width, int height) {
  if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
    fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError());
//return NULL;
    exit(1);
  }

  SDL_Window *window = SDL_CreateWindow(
    "sdl2",
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    width, height,
    0
  );
  if (window == NULL) {
    printf("Unable to create window: %s\n", SDL_GetError());
// return NULL;
    exit(1);
  }

  SDL_Renderer *renderer = SDL_CreateRenderer(
    window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
  );
  if (renderer == NULL) {
    SDL_DestroyWindow(window);
    fprintf(stderr, "Unable to create renderer: %s\n", SDL_GetError());
    exit(1);
  }

  if (SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND) != 0) {
    fprintf(stderr, "SDL_BlendMode failed: %s\n", SDL_GetError());
    exit(1);
  };

  return renderer;
}

void filledRect(SDL_Renderer* renderer,
                int x, int y, int w, int h,
                int r, int g, int b, int a)
{
    int rc1 = SDL_SetRenderDrawColor(renderer, r, g, b, a);
    if (rc1 != 0) {
      fprintf(stderr, "SDL_SetRenderDrawColor failed: %s\n", SDL_GetError());
      exit(1);
    }
    SDL_Rect rect = { x, y, w, h };
    int rc2 = SDL_RenderFillRect(renderer, &rect);
    if (rc2 != 0) {
      fprintf(stderr, "SDL_RenderFillRect failed: %s\n", SDL_GetError());
      exit(1);
    }
}

void filledEllipse(SDL_Renderer* renderer,
                   int x, int y, int rx, int ry,
                   int r, int g, int b, int a)
{
    filledEllipseRGBA(renderer, x, y, rx, ry, r, g, b, a);
}

void drawLine(SDL_Renderer* renderer,
              int x, int y, int ex, int ey,
              int r, int g, int b, int a)
{
    lineRGBA(renderer, x, y, ex, ey, r, g, b, a);
}

VAL MOTION(VM* vm, int x, int y, int relx, int rely) {
    VAL m;
    idris_constructor(m, vm, 2, 4, 0);
    idris_setConArg(m, 0, MKINT((intptr_t)x));
    idris_setConArg(m, 1, MKINT((intptr_t)y));
    idris_setConArg(m, 2, MKINT((intptr_t)relx));
    idris_setConArg(m, 3, MKINT((intptr_t)rely));
    return m;
}

VAL BUTTON(VM* vm, int tag, int b, int x, int y) {
    VAL button;

    switch(b) {
    case SDL_BUTTON_LEFT:
        idris_constructor(button, vm, 0, 0, 0);
        break;
    case SDL_BUTTON_MIDDLE:
        idris_constructor(button, vm, 1, 0, 0);
        break;
    case SDL_BUTTON_RIGHT:
        idris_constructor(button, vm, 2, 0, 0);
        break;
// TODO: The handling of mouse wheel events has changed in SDL2.
/*
    case SDL_BUTTON_WHEELUP:
        idris_constructor(button, vm, 3, 0, 0);
        break;
    case SDL_BUTTON_WHEELDOWN:
        idris_constructor(button, vm, 4, 0, 0);
        break;
*/
    default:
        idris_constructor(button, vm, 0, 0, 0);
        break;
    }

    VAL event;
    idris_constructor(event, vm, tag, 3, 0);
    idris_setConArg(event, 0, button);
    idris_setConArg(event, 1, MKINT((intptr_t)x));
    idris_setConArg(event, 2, MKINT((intptr_t)y));

    return event;
}

VAL RESIZE(VM* vm, int w, int h) {
    VAL m;
    idris_constructor(m, vm, 5, 2, 0);
    idris_setConArg(m, 0, MKINT((intptr_t)w));
    idris_setConArg(m, 1, MKINT((intptr_t)h));
    return m;
}

VAL KEY(VM* vm, int tag, SDL_Keycode key) {
    VAL k;

    switch(key) {
    case SDLK_UP:
        idris_constructor(k, vm, 0, 0, 0);
        break;
    case SDLK_DOWN:
        idris_constructor(k, vm, 1, 0, 0);
        break;
    case SDLK_LEFT:
        idris_constructor(k, vm, 2, 0, 0);
        break;
    case SDLK_RIGHT:
        idris_constructor(k, vm, 3, 0, 0);
        break;
    case SDLK_ESCAPE:
        idris_constructor(k, vm, 4, 0, 0);
        break;
    case SDLK_SPACE:
        idris_constructor(k, vm, 5, 0, 0);
        break;
    case SDLK_TAB:
        idris_constructor(k, vm, 6, 0, 0);
        break;
    case SDLK_F1:
        idris_constructor(k, vm, 7, 0, 0);
        break;
    case SDLK_F2:
        idris_constructor(k, vm, 8, 0, 0);
        break;
    case SDLK_F3:
        idris_constructor(k, vm, 9, 0, 0);
        break;
    case SDLK_F4:
        idris_constructor(k, vm, 10, 0, 0);
        break;
    case SDLK_F5:
        idris_constructor(k, vm, 11, 0, 0);
        break;
    case SDLK_F6:
        idris_constructor(k, vm, 12, 0, 0);
        break;
    case SDLK_F7:
        idris_constructor(k, vm, 13, 0, 0);
        break;
    case SDLK_F8:
        idris_constructor(k, vm, 14, 0, 0);
        break;
    case SDLK_F9:
        idris_constructor(k, vm, 15, 0, 0);
        break;
    case SDLK_F10:
        idris_constructor(k, vm, 16, 0, 0);
        break;
    case SDLK_F11:
        idris_constructor(k, vm, 17, 0, 0);
        break;
    case SDLK_F12:
        idris_constructor(k, vm, 18, 0, 0);
        break;
    case SDLK_F13:
        idris_constructor(k, vm, 19, 0, 0);
        break;
    case SDLK_F14:
        idris_constructor(k, vm, 20, 0, 0);
        break;
    case SDLK_F15:
        idris_constructor(k, vm, 21, 0, 0);
        break;
    case SDLK_LSHIFT:
        idris_constructor(k, vm, 22, 0, 0);
        break;
    case SDLK_RSHIFT:
        idris_constructor(k, vm, 23, 0, 0);
        break;
    case SDLK_LCTRL:
        idris_constructor(k, vm, 24, 0, 0);
        break;
    case SDLK_RCTRL:
        idris_constructor(k, vm, 25, 0, 0);
        break;
    default:
        idris_constructor(k, vm, 26, 1, 0);
        // safe because there's no further allocation.
        idris_setConArg(k, 0, MKINT((intptr_t)key));
        break;
    }

    VAL event;
    idris_constructor(event, vm, tag, 1, 0);
    idris_setConArg(event, 0, k);

    return event;
}

/*
data Button = Left | Middle | Right | WheelUp | WheelDown

data Event = KeyDown Key
           | KeyUp Key
           | MouseMotion Int Int Int Int
           | MouseButtonDown Button Int Int
           | MouseButtonUp Button Int Int
           | AppQuit

pollEvent : IO (Maybe Event)
*/

void* pollEvent(VM* vm) {
    VAL idris_event;

    SDL_Event event; // = (SDL_Event *) GC_MALLOC(sizeof(SDL_Event));
    int r = SDL_PollEvent(&event);

    idris_requireAlloc(128); // Conservative!

    if (r==0) {
        idris_constructor(idris_event, vm, 0, 0, 0); // Nothing
    }
    else {
        VAL ievent = NULL;
        switch(event.type) {
        case SDL_KEYDOWN:
            ievent = KEY(vm, 0, event.key.keysym.sym);
            break;
        case SDL_KEYUP:
            ievent = KEY(vm, 1, event.key.keysym.sym);
            break;
        case SDL_MOUSEMOTION:
            ievent = MOTION(vm, event.motion.x, event.motion.y,
                                event.motion.xrel, event.motion.yrel);
            break;
        case SDL_MOUSEBUTTONDOWN:
            ievent = BUTTON(vm, 3, event.button.button,
                                event.button.x, event.button.y);
            break;
        case SDL_MOUSEBUTTONUP:
            ievent = BUTTON(vm, 4, event.button.button,
                                event.button.x, event.button.y);
            break;
        case SDL_WINDOWEVENT:
            if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
              ievent = RESIZE(vm, event.window.data1, event.window.data2);
            }
            break;
        case SDL_QUIT:
            idris_constructor(ievent, vm, 6, 0, 0);
            break;
        default:
            idris_constructor(idris_event, vm, 0, 0, 0); // Nothing
            idris_doneAlloc(vm);
            return idris_event;
        }
        idris_constructor(idris_event, vm, 1, 1, 0);
        idris_setConArg(idris_event, 0, ievent); // Just ievent
    }

    idris_doneAlloc(vm);
    return idris_event;
}

// FIXME: Remove this when events work.
int pollEventsForQuit() {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    switch (e.type) {
      case SDL_QUIT:
        return 1;
        break;
      case SDL_KEYDOWN:
        if (e.key.keysym.sym == SDLK_ESCAPE) {
          return 1;
        }
        break;
    }
  }
  return 0;
}
