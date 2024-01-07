#pragma once
#include <definitions.hpp>

#include <SDL2/SDL.h>
#include <backends/imgui_impl_sdl2.h>
#include <backends/imgui_impl_sdlrenderer2.h>
#include <imgui.h>

#include "./Vector.hpp"

SDL_Window *NewWindow();
SDL_Renderer *NewRenderer(SDL_Window *window);
void Setup(SDL_Window *window, SDL_Renderer *renderer, ImGuiIO &io);
void MainLoop(SDL_Window *window, SDL_Renderer *renderer, ImGuiIO &io);
void Shutdown(SDL_Window *window, SDL_Renderer *renderer);
int CreateApp();

inline static ImVec2 GetWindowCenter()
{
    ImVec2 win_pos = ImGui::GetWindowPos();
    ImVec2 win_size = ImGui::GetWindowSize();
    ImVec2 win_center = ImVec2(win_pos.x + win_size.x * 0.5f, win_pos.y + win_size.y * 0.5f);
    return win_center;
}

inline void CreateCanvas()
{
    ImVec2 canvas_p0 = ImGui::GetCursorScreenPos();    // ImDrawList API uses screen coordinates!
    ImVec2 canvas_sz = ImGui::GetContentRegionAvail(); // Resize canvas to what's available
    ImVec2 canvas_p1 = ImVec2(canvas_p0.x + canvas_sz.x, canvas_p0.y + canvas_sz.y);

    ImDrawList *draw_list = ImGui::GetWindowDrawList();
    draw_list->AddRectFilled(canvas_p0, canvas_p1, IM_COL32(50, 50, 50, 255));
}

inline static void ShowExampleAppCustomRendering()
{
    if (!ImGui::BeginChild("Example: Custom rendering"))
    {
        ImGui::End();
        return;
    }

    const ImVec2 win_pos = ImGui::GetWindowPos();
    const ImVec2 win_size = ImGui::GetWindowSize();
    const ImVec2 win_center = GetWindowCenter();

    const ImColor color{0xFF, 0xFF, 0xFF};
    static int phase = 0;
    Vector v1{100, static_cast<double>(phase++)};

    CreateCanvas();
    DrawVector(v1, win_center);

    printf("Win pos: %f %f\t", win_pos.x, win_pos.y);
    // printf("Win siz: %f %f\n", win_size.x, win_size.y);

    ImGui::EndChild();
}
