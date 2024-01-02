#pragma once
#include <cmath>
#include <definitions.hpp>

#include <SDL2/SDL.h>
#include <backends/imgui_impl_sdl2.h>
#include <backends/imgui_impl_sdlrenderer2.h>
#include <imgui.h>

SDL_Window *NewWindow();
SDL_Renderer *NewRenderer(SDL_Window *window);
void Setup(SDL_Window *window, SDL_Renderer *renderer, ImGuiIO &io);
void MainLoop(SDL_Window *window, SDL_Renderer *renderer, ImGuiIO &io);
void Shutdown(SDL_Window *window, SDL_Renderer *renderer);
int CreateApp();

inline static ImVec2 GetWindowCenter()
{
    ImVec2 window_pos = ImGui::GetWindowPos();
    ImVec2 window_size = ImGui::GetWindowSize();
    ImVec2 window_center = ImVec2(window_pos.x + window_size.x * 0.5f, window_pos.y + window_size.y * 0.5f);
    return window_center;
}

inline static void HelpMarker(const char *desc)
{
    ImGui::TextDisabled("(?)");
    if (ImGui::BeginItemTooltip())
    {
        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
        ImGui::TextUnformatted(desc);
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }
}

inline void CreateCanvas()
{
    ImVec2 canvas_p0 = ImGui::GetCursorScreenPos();    // ImDrawList API uses screen coordinates!
    ImVec2 canvas_sz = ImGui::GetContentRegionAvail(); // Resize canvas to what's available
    ImVec2 canvas_p1 = ImVec2(canvas_p0.x + canvas_sz.x, canvas_p0.y + canvas_sz.y);

    const ImGuiIO &io = ImGui::GetIO();
    ImDrawList *draw_list = ImGui::GetWindowDrawList();
    draw_list->AddRectFilled(canvas_p0, canvas_p1, IM_COL32(50, 50, 50, 255));
    draw_list->AddRect(canvas_p0, canvas_p1, IM_COL32(255, 255, 255, 255));
}

inline void CreateVector(ImDrawList *draw_list, const ImVec2 &pos, ImU32 color, float size,
                         const ImVec2 &offset = {0.0f, 0.0f})
{
    float x = pos.x + offset.x, y = pos.y + offset.y;
    ImVec2 p1(x, y);
    ImVec2 p2(x + size, y + size);

    ImVec2 dir(p2.x - p1.x, p2.y - p1.y);
    float dir_mag = 1.0f / std::sqrt((dir.x * dir.x) + (dir.y * dir.y));
    ImVec2 dir_norm = {dir.x * dir_mag, dir.y * dir_mag};
    ImVec2 dir_perp = {-dir_norm.x, dir_norm.y};

    float arrowhead_length = 10.0f;
    ImVec2 p3{p2.x - arrowhead_length * 0.5f * dir_norm.x - arrowhead_length * 0.5f * dir_perp.x,
              p2.y - arrowhead_length * 0.5f * dir_norm.y - arrowhead_length * 0.5f * dir_perp.y};
    ImVec2 p4{p2.x - arrowhead_length * 0.5f * dir_norm.x + arrowhead_length * 0.5f * dir_perp.x,
              p2.y - arrowhead_length * 0.5f * dir_norm.y + arrowhead_length * 0.5f * dir_perp.y};

    draw_list->AddLine(p1, p2, color);
    draw_list->AddTriangleFilled(p2, p3, p4, color);
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

    ImDrawList *draw_list = ImGui::GetWindowDrawList();

    CreateCanvas();
    CreateVector(draw_list, win_pos, ImColor(0xFF, 0xFF, 0xFF), 100.0f, {10.0f, 10.0f});

    printf("Window pos: %f %f\t", win_pos.x, win_pos.y);
    printf("Window siz: %f %f\n", win_size.x, win_size.y);

    ImGui::EndChild();
}
