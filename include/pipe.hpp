#pragma once

#include "SDL3/SDL_rect.h"
#include <utility>

class Pipe {
  public:
    // constructor
    Pipe();

    // getters
    std::pair<SDL_FRect, SDL_FRect> &Rect();
    void Respawn();

  private:
    std::pair<SDL_FRect, SDL_FRect> rect;
    float spawnTime = 0;
};
