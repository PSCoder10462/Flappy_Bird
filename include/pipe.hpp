#pragma once

#include "SDL3/SDL_rect.h"
#include <utility>

class Pipe {
  public:
    // constructor
    Pipe();

    // getters
    const std::pair<SDL_FRect, SDL_FRect> &Rect();

  private:
    std::pair<SDL_FRect, SDL_FRect> rect;
};
