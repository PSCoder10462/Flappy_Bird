#define SDL_MAIN_USE_CALLBACKS 1 /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

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
    SDL_SetRenderLogicalPresentation(renderer, 640, 480,
                                     SDL_LOGICAL_PRESENTATION_LETTERBOX);

    return SDL_APP_CONTINUE; /* carry on with the program! */
}

/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS; /* end the program, reporting success to the OS.
                                 */
    }
    return SDL_APP_CONTINUE; /* carry on with the program! */
}

/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(void *appstate) {
    const double now = ((double)SDL_GetTicks()) /
                       1000.0; /* convert from milliseconds to seconds. */
    /* choose the color for the frame we will draw. The sine wave trick makes it
     * fade between colors smoothly. */
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
