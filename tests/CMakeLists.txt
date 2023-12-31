# ./tests/CMakeLists.txt
enable_testing()

# Misc test
add_executable(main_test main_test.cpp)
add_test(NAME main_test COMMAND $<TARGET_FILE:main_test>)

# SDL2 renderer example test
add_executable(imgui_test imgui_test.cpp)
target_link_libraries(imgui_test PRIVATE imgui ${SDL2_LIBRARIES})
target_include_directories(imgui_test PRIVATE ${CMAKE_SOURCE_DIR}/lib/imgui ${SDL2_INCLUDE_DIRS})
add_test(NAME imgui_test COMMAND $<TARGET_FILE:imgui_test>)


add_custom_target(run_all_tests
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/tests
    COMMENT "Running tests"
)
