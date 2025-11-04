#pragma once

#include "SDL3/SDL_rect.h"

class Bird {
  public:
    // c'tor
    Bird();

    // getters
    const SDL_FRect &Rect() const;

    // setters
    // void Rect(const std::pair<float, float> &value);

  private:
    SDL_FRect rect;
};
