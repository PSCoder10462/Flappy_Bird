#include "SDL3/SDL_timer.h"
#include <score.hpp>

std::string Score::getScore() {
    auto score = static_cast<int>(1.0f * SDL_GetTicks() / 1000.0f) / 5;
    return "Score: " + std::to_string(score);
}
