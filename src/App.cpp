#include "./App.hpp"
#include "imgui.h"

SDL_Window *NewWindow() {
    SDL_Window *window = SDL_CreateWindow(WIN_SETTINGS.title, WIN_SETTINGS.x, WIN_SETTINGS.y, WIN_SETTINGS.w,
                                          WIN_SETTINGS.h, WIN_SETTINGS.window_flags);
    if (window == nullptr) {
        printf("Error: SDL_CreateWindow(): %s\n", SDL_GetError());
        exit(-1);
    }
    return window;
}

SDL_Renderer *NewRenderer(SDL_Window *window) {
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        SDL_Log("Error creating SDL_Renderer!");
        exit(0);
    }
    SDL_RendererInfo info;
    SDL_GetRendererInfo(renderer, &info);
    SDL_Log("Current SDL_Renderer: %s", info.name);
    return renderer;
}

void Setup(SDL_Window *window, SDL_Renderer *renderer, ImGuiIO &io) {
    IMGUI_CHECKVERSION();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    // ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer2_Init(renderer);
}

void MainLoop(SDL_Window *window, SDL_Renderer *renderer, ImGuiIO &io) {
    bool done = false;
    while (!done) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT)
                done = true;
            if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE &&
                event.window.windowID == SDL_GetWindowID(window))
                done = true;
        }
        // Start the Dear ImGui frame
        ImGui_ImplSDLRenderer2_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        {
            ShowExampleAppCustomRendering();
        }

        // Rendering
        ImGui::Render();
        SDL_RenderSetScale(renderer, io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
        SDL_RenderClear(renderer);
        ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
        SDL_RenderPresent(renderer);
    }
}

void Shutdown(SDL_Window *window, SDL_Renderer *renderer) {
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int CreateApp() {
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
    Shutdown(window, renderer);
    return 0;
}
