# ./lib/CMakeLists.txt
cmake_minimum_required(VERSION 3.21)
include(FetchContent)

# Add and build the ImGui library from the 'lib' directory
set(IMGUI_SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/imgui")
if(NOT EXISTS ${IMGUI_SOURCE_DIR})
    message(STATUS "Fetching ImGui repository")
    FetchContent_Declare(imgui
        GIT_REPOSITORY "https://github.com/ocornut/imgui.git"
        GIT_TAG "origin/master"
        SOURCE_DIR ${IMGUI_SOURCE_DIR}
    )
    FetchContent_MakeAvailable(imgui)
endif()

set(IMGUI_SOURCE_FILES
    ${IMGUI_SOURCE_DIR}/imgui.cpp
    ${IMGUI_SOURCE_DIR}/imgui_demo.cpp
    ${IMGUI_SOURCE_DIR}/imgui_draw.cpp
    ${IMGUI_SOURCE_DIR}/imgui_tables.cpp
    ${IMGUI_SOURCE_DIR}/imgui_widgets.cpp
    ${IMGUI_SOURCE_DIR}/backends/imgui_impl_sdl2.cpp
    ${IMGUI_SOURCE_DIR}/backends/imgui_impl_sdlrenderer2.cpp
)
add_library(imgui STATIC ${IMGUI_SOURCE_FILES})
target_include_directories(imgui PRIVATE ${IMGUI_SOURCE_DIR} ${SDL2_INCLUDE_DIRS})
target_link_libraries(imgui PRIVATE ${SDL2_LIBRARIES} GL dl)
