#pragma once
#include "imgui.h"
#include <cmath>
#include <cstdio>
#include <numbers>

struct Vector
{
    double module, angle;
    ImVec2 pt_xy;

    constexpr Vector(double module, double angle)
        : module(module), angle(angle), pt_xy(GetRectCord(module, angle))
    {
    }

    static constexpr ImVec2 GetRectCord(float mod, float angle)
    {
        double rad = angle * std::numbers::pi / 180.f;
        return ImVec2(mod * cos(rad), mod * sin(rad));
    }

    constexpr Vector operator+(const Vector &v2)
    {
        return {this->pt_xy.x + v2.pt_xy.x, this->pt_xy.y + v2.pt_xy.y};
    }
    constexpr ImVec2 operator+(const ImVec2 &v2)
    {
        return {this->pt_xy.x + v2.x, this->pt_xy.y + v2.y};
    }
    constexpr explicit operator ImVec2() { return ImVec2{this->pt_xy.x, this->pt_xy.y}; }
};

/**
 * @brief Draw a vector into the active window
 *
 * @param origin Vecto's tail position
 * @param mod Vector's module
 * @param angle Vector's angle in deg
 * @param color Vector's color def {0xFF, 0xFF, 0xFF}
 */
inline void DrawVector(Vector &vector, const ImVec2 &origin = {0, 0},
                       ImColor color = {0xFF, 0xFF, 0xFF})
{
    ImDrawList *draw_list = ImGui::GetWindowDrawList();

    const ImVec2 &p1 = origin;
    ImVec2 p2 = vector + origin;
    p2.x = vector.pt_xy.x, p2.y = vector.pt_xy.y;

    auto vec_mag = [](const ImVec2 &v) { return sqrt(v.x * v.x + v.y * v.y); };
    auto vec_ang = [](const ImVec2 &v) { return atan(v.y / v.x) * 180 / std::numbers::pi; };
    printf("P1: %f, %f | Mod: %f | Ang: %f | \t", p1.x, p1.y, vec_mag(p1), vec_ang(p1));
    printf("P2: %f, %f | Mod: %f | Ang: %f | \n", p2.x, p2.y, vec_mag(p2), vec_ang(p2));

    ImVec2 dir{p2.x - origin.x, p2.y - origin.y};
    float dir_mag = 1.0f / std::sqrt((dir.x * dir.x) + (dir.y * dir.y));
    ImVec2 dir_norm = {dir.x * dir_mag, dir.y * dir_mag};
    ImVec2 dir_perp = {-dir_norm.x, dir_norm.y};

    float arrowhead_length = 10.0f;
    ImVec2 p3{p2.x - arrowhead_length * 0.5f * dir_norm.x - arrowhead_length * 0.5f * dir_perp.x,
              p2.y - arrowhead_length * 0.5f * dir_norm.y - arrowhead_length * 0.5f * dir_perp.y};
    ImVec2 p4{p2.x - arrowhead_length * 0.5f * dir_norm.x + arrowhead_length * 0.5f * dir_perp.x,
              p2.y - arrowhead_length * 0.5f * dir_norm.y + arrowhead_length * 0.5f * dir_perp.y};

    draw_list->AddLine(origin, p2, color);
    draw_list->AddTriangleFilled(p2, p3, p4, color);
}
