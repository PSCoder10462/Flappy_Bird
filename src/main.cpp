#include "SDL3/SDL_events.h"
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_scancode.h"
#define SDL_MAIN_USE_CALLBACKS 1 /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include <string>

#include "bird.hpp"
#include "constants.hpp"

/* We will use this renderer to draw into this window every frame. */
static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static Bird bird;

/* This function runs once at startup. */
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]) {
    SDL_SetAppMetadata("Example Renderer Clear", "1.0",
                       "com.example.renderer-clear");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer("examples/renderer/clear", c_windowWidth,
                                     c_windowHeight, SDL_WINDOW_RESIZABLE,
                                     &window, &renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    SDL_SetRenderLogicalPresentation(renderer, c_windowWidth, c_windowHeight,
                                     SDL_LOGICAL_PRESENTATION_LETTERBOX);

    return SDL_APP_CONTINUE; /* carry on with the program! */
}


static void s_handleKeyDown(const SDL_Scancode& scancode) {
    if (scancode== SDL_SCANCODE_SPACE)
        bird.Jump();
}

/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
    switch (event->type) {
    case SDL_EVENT_QUIT:
        return SDL_APP_SUCCESS;
        break;
    case SDL_EVENT_KEY_DOWN:
        s_handleKeyDown(event->key.scancode);
    default:
        return SDL_APP_CONTINUE; /* carry on with the program! */
    }
}

/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(void *appstate) {
    SDL_SetRenderDrawColor(
        renderer, c_skyRGB[0], c_skyRGB[1], c_skyRGB[2],
        SDL_ALPHA_OPAQUE_FLOAT); /* new color, full alpha. */
    /* clear the window to the draw color. */
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, c_birdRGB[0], c_birdRGB[1], c_birdRGB[2],
                           SDL_ALPHA_OPAQUE); /* blue, full alpha */
    SDL_RenderFillRect(renderer, &bird.Rect());

    /* put the newly-cleared rendering on the screen. */
    SDL_RenderPresent(renderer);


    return SDL_APP_CONTINUE; /* carry on with the program! */
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void *appstate, SDL_AppResult result) {
    /* SDL will clean up the window/renderer for us. */
}
