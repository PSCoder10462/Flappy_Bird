#include "SDL3/SDL_timer.h"
#include <bird.hpp>
#include <constants.hpp>

float upSpeed = c_birdJumpSpeed;

static float jumpTime = 0;
static float prevY = (c_windowHeight - c_birdHeight) / 2.0;

Bird::Bird() {
    rect.x = 20.0;
    rect.y = (c_windowHeight - c_birdHeight) / 2.0;
    rect.h = c_birdHeight;
    rect.w = c_birdWidth;
}

// getters
const SDL_FRect &Bird::Rect() {
    auto now = (1.0 * SDL_GetTicks()) / 1000.0;
    if (now > jumpTime) {
        auto t = now - jumpTime;
        float dist = (upSpeed * t) + (0.5 * c_gravity * t * t);
        rect.y = (dist + prevY);
        if (rect.y < 0)
            rect.y = 0, upSpeed = 0, prevY = 0;
        if (rect.y + c_birdHeight > c_windowHeight) {
            rect.y = c_windowHeight - c_birdHeight;
        }
    }
    return rect;
}

void Bird::Jump() {
    jumpTime = (1.0 * SDL_GetTicks()) / 1000.0;
    prevY = rect.y;
    upSpeed = c_birdJumpSpeed;
}

void Bird::Reset() {
    rect.x = 20.0;
    rect.y = (c_windowHeight - c_birdHeight) / 2.0;
    rect.h = c_birdHeight;
    rect.w = c_birdWidth;
    jumpTime = (1.0 * SDL_GetTicks()) / 1000.0;
    prevY = (c_windowHeight - c_birdHeight) / 2.0;
}
