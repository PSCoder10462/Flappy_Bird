#include <bird.hpp>

// c'tor
Bird::Bird() {
    rect.x = rect.y = rect.h = rect.w = 20;
}

// getters

const SDL_FRect &Bird::Rect() const { return rect; }
