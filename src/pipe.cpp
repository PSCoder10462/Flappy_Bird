#include "SDL3/SDL_stdinc.h"
#include "SDL3/SDL_timer.h"
#include "constants.hpp"
#include <pipe.hpp>

static float spawnTime = 0;

Pipe::Pipe() {
    spawnTime = (1.0 * SDL_GetTicks()) / 1000.0;

    rect.first.x = c_windowWidth;
    rect.first.y = 0;
    rect.first.h = c_windowHeight * SDL_randf();
    rect.first.w = c_pipeWidth;

    rect.second.x = c_windowWidth;
    rect.second.y = rect.first.h + c_pipeGap;
    rect.second.h = c_windowHeight - (rect.first.h + c_pipeGap);
    rect.second.w = c_pipeWidth;
}

const std::pair<SDL_FRect, SDL_FRect> &Pipe::Rect() {
    auto now = (1.0f * SDL_GetTicks()) / 1000.0;

    float t = now - spawnTime;
    rect.first.x = c_windowWidth + c_pipeSpeed * t;
    rect.second.x = c_windowWidth + c_pipeSpeed * t;
    return rect;
}
