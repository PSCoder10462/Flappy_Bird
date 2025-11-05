#include "SDL3/SDL_timer.h"
#include <score.hpp>

int Score::score = 0;
float Score::startTime = (1.0f * SDL_GetTicks() / 1000.0f);

std::string Score::getScore() {
    score =
        static_cast<int>((1.0f * SDL_GetTicks() / 1000.0f) - startTime) / 5;
    return "Score: " + std::to_string(score);
}

void Score::Reset() {
    startTime = (1.0f * SDL_GetTicks() / 1000.0f);
    score = 0;
}
