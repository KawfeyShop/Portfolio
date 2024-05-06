cmake_minimum_required(VERSION 3.29.0)

project(yahtzee)

# Set the output directory for executables to the bin folder inside the build directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/bin)

# Add yahtzee executable
add_executable(yahtzee ${PROJECT_SOURCE_DIR}/yahtzee.cpp ${PROJECT_SOURCE_DIR}/yahtzee.h)

# Add tests executable
add_executable(yahtzeeTest ${PROJECT_SOURCE_DIR}/tests/tests.cpp)

# Include the catch.hpp file directly in your test file
target_include_directories(yahtzeeTest PRIVATE ${PROJECT_SOURCE_DIR}/tests)

# Custom target to build only yahtzee
add_custom_target(build_yahtzee
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target yahtzee
    COMMENT "Building only tests"
)

# Custom target to build only tests
add_custom_target(build_test
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target yahtzeeTest
    COMMENT "Building only tests"
)

# Custom target to clean the build directory
add_custom_target(clean_build
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}
    COMMENT "Cleaning up build directory..."
)
