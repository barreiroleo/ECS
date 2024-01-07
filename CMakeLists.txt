# ./CMakeLists.txt
cmake_minimum_required(VERSION 3.22.1)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(ECS)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SOURCE_FILES
    src/main.cpp
    src/App.cpp
    src/Vector.hpp
)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# Dependencies
find_package(SDL2 REQUIRED)
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/include/
    ${CMAKE_SOURCE_DIR}/lib/imgui
    ${SDL2_INCLUDE_DIRS}
)
add_subdirectory(${CMAKE_SOURCE_DIR}/lib/)

set_target_properties( ${PROJECT_NAME}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Link the main executable with ImGui and SDL2 libraries
target_link_libraries(${PROJECT_NAME} imgui ${SDL2_LIBRARIES})

add_subdirectory(tests)
