#pragma once

#include "SDL3/SDL_rect.h"

class Bird {
  public:
    // constructor
    Bird();

    // getters
    const SDL_FRect &Rect();
    void Jump();

  private:
    SDL_FRect rect;
};
