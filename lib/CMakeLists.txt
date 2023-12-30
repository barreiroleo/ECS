cmake_minimum_required(VERSION 3.21)

include(FetchContent)
FetchContent_Declare(imgui
  GIT_REPOSITORY "https://github.com/ocornut/imgui.git"
  GIT_TAG "origin/master"
  SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/imgui"
)
FetchContent_MakeAvailable(imgui)

# ImGui
set(IMGUI_DIR ${PROJECT_SOURCE_DIR}/lib/imgui)
set(IMGUI_SOURCE_FILES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/backends/imgui_impl_sdl2.cpp
    ${IMGUI_DIR}/backends/imgui_impl_sdlrenderer2.cpp
)
add_library(imgui STATIC ${IMGUI_SOURCE_FILES})

# SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} ${IMGUI_DIR})
link_libraries(${SDL2_LIBRARIES} imgui GL dl)
