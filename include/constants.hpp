#pragma once

#include "SDL3/SDL_stdinc.h"
#include <vector>

const float c_gravity = 1000.0;

const int c_windowWidth = 1280;
const int c_windowHeight = 720;

const float c_birdWidth = 40;
const float c_birdHeight = 40;
const float c_birdJumpSpeed = -350.0f;

const float c_pipeGap = 150.0f;
const float c_pipeWidth = 100.0f;
const float c_pipeSpeed = -100.0f;
const int c_pipeSpawnTime = 6;

const std::vector<Uint8> c_skyRGB = {135, 206, 235};
const std::vector<Uint8> c_birdRGB = {54, 128, 45};
const std::vector<Uint8> c_pipeRGB = {203, 44, 49};


