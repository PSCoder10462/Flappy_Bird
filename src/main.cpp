#include "SDL3/SDL_events.h"
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_scancode.h"
#include "pipe.hpp"
#include "score.hpp"
#define SDL_MAIN_USE_CALLBACKS 1 /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "bird.hpp"
#include "constants.hpp"

/* We will use this renderer to draw into this window every frame. */
static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static Bird bird;
static std::vector<Pipe> pipes;
static int spawnNeeded = c_pipeSpawnTime;
static int pipeIdx = 0;

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

static void s_restartGame() {
    bird.Reset();
    Score::Reset();
    pipes.clear();
}

static void s_handleKeyDown(const SDL_Scancode &scancode) {
    if (scancode == SDL_SCANCODE_SPACE)
        bird.Jump();
    else if (scancode == SDL_SCANCODE_R)
        s_restartGame();
}

static void s_checkCollision() {
    // bird, pipe
    auto checkOverlapIntervals = [](const float &a, const float &b,
                                    const float &x, const float &y) {
        if (b < x || a > y)
            return false;
        return true;
    };

    bool collisionX = false;
    bool collisionY = false;
    for (auto &pipe : pipes) {
        // horizontal
        auto bx = bird.Rect().x;
        auto bxEnd = bx + c_birdWidth;
        auto px = pipe.Rect().first.x;
        auto pxEnd = px + c_pipeWidth;
        collisionX = checkOverlapIntervals(bx, bxEnd, px, pxEnd);

        // vertical
        auto by = bird.Rect().y;
        auto byEnd = by + c_birdHeight;
        auto py1 = pipe.Rect().first.y;
        auto py1End = py1 + pipe.Rect().first.h;
        auto py2 = pipe.Rect().second.y;
        auto py2End = py2 + pipe.Rect().second.h;

        collisionY = checkOverlapIntervals(by, byEnd, py1, py1End) ||
                     checkOverlapIntervals(by, byEnd, py2, py2End);

        if (collisionX && collisionY) break;
    }

    if (collisionX && collisionY)
        s_restartGame();
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
    SDL_SetRenderDrawColor(renderer, c_skyRGB[0], c_skyRGB[1], c_skyRGB[2],
                           SDL_ALPHA_OPAQUE_FLOAT); /* new color, full alpha. */
    /* clear the window to the draw color. */
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, c_birdRGB[0], c_birdRGB[1], c_birdRGB[2],
                           SDL_ALPHA_OPAQUE); /* blue, full alpha */
    SDL_RenderFillRect(renderer, &bird.Rect());

    SDL_SetRenderDrawColor(renderer, c_pipeRGB[0], c_pipeRGB[1], c_pipeRGB[2],
                           SDL_ALPHA_OPAQUE); /* blue, full alpha */

    auto now = static_cast<int>((1.8f * SDL_GetTicks()) / 1000.0);

    for (auto &pipe : pipes) {
        SDL_RenderFillRect(renderer, &(pipe.Rect().first));
        SDL_RenderFillRect(renderer, &(pipe.Rect().second));
    }

    if (now == spawnNeeded) {
        if (pipes.size() < 5) {
            Pipe pipe;
            pipes.push_back(pipe);
            spawnNeeded += c_pipeSpawnTime;
        } else if (pipes[pipeIdx].Rect().first.x +
                       pipes[pipeIdx].Rect().first.w <
                   0) {
            pipes[pipeIdx].Respawn();
            spawnNeeded += c_pipeSpawnTime;
            pipeIdx = (pipeIdx + 1) % 5;
        }
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255,
                           SDL_ALPHA_OPAQUE); /* white, full alpha */
    SDL_SetRenderScale(renderer, 3.0f, 3.0f);
    SDL_RenderDebugText(renderer, 10, 10, Score::getScore().c_str());
    SDL_SetRenderScale(renderer, 1.0f, 1.0f);

    s_checkCollision();

    /* put the newly-cleared rendering on the screen. */
    SDL_RenderPresent(renderer);

    return SDL_APP_CONTINUE; /* carry on with the program! */
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void *appstate, SDL_AppResult result) {
    /* SDL will clean up the window/renderer for us. */
}
