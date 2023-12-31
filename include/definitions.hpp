#pragma once

#include <SDL.h>

const struct WIN_SETTINGS {
    const char *title = "ECS - Electric component system";
    int x = SDL_WINDOWPOS_CENTERED;
    int y = SDL_WINDOWPOS_CENTERED;
    int w = 1280;
    int h = 720;
    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
} WIN_SETTINGS;
