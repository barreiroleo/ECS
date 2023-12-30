enable_testing()

add_executable(main_test main_test.cpp)
# target_link_libraries(main_test PRIVATE project_library)
add_test(NAME main_test COMMAND $<TARGET_FILE:main_test>)

add_custom_target(run_all_tests
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/tests
    COMMENT "Running tests"
)
