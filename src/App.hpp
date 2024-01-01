#pragma once
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

inline static void HelpMarker(const char *desc) {
    ImGui::TextDisabled("(?)");
    if (ImGui::BeginItemTooltip()) {
        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
        ImGui::TextUnformatted(desc);
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }
}

inline static void ShowExampleAppCustomRendering() {
    if (!ImGui::Begin("Example: Custom rendering")) {
        ImGui::End();
        return;
    }

    {
        ImGui::PushItemWidth(-ImGui::GetFontSize() * 15);
        ImDrawList *draw_list = ImGui::GetWindowDrawList();

        static float size = 100.0f;
        const ImVec2 p = ImGui::GetCursorScreenPos();
        const ImU32 color = ImColor(0xFF, 0xFF, 0xFF);
        float x = p.x + 4.0f;
        float y = p.y + 4.0f;
        {
            draw_list->AddTriangle(ImVec2(x + size * 0.2f, y), ImVec2(x, y + size - 0.5f),
                                   ImVec2(x + size * 0.4f, y + size - 0.5f), color);
            draw_list->AddLine(ImVec2(x, y), ImVec2(x + size, y + size), color);
        }
    }

    ImGui::End();
}
