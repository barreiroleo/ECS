#pragma once
#include <definitions.hpp>

#include <imgui.h>
#include <backends/imgui_impl_sdl2.h>
#include <backends/imgui_impl_sdlrenderer2.h>
#include <SDL2/SDL.h>

SDL_Window *NewWindow();
SDL_Renderer *NewRenderer(SDL_Window *window);
void Setup(SDL_Window *window, SDL_Renderer *renderer, ImGuiIO& io);
void MainLoop(SDL_Window* window, SDL_Renderer* renderer, ImGuiIO& io);

inline int CreateApp() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0) {
        printf("Error: %s\n", SDL_GetError());
        return -1;
    }
    SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");

    SDL_Window *window = NewWindow();
    SDL_Renderer *renderer = NewRenderer(window);
    // Setup Dear ImGui context
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();

    Setup(window, renderer, io);
    MainLoop(window, renderer, io);

    // Cleanup
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
