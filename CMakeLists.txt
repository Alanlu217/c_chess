cmake_minimum_required(VERSION 3.30)

include(cmake/zig.cmake)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_FLAGS "-Wno-macro-redefined")

project(chess)

add_subdirectory(vendor/raylib)

add_executable(chess
    "src/main.c"
)

target_link_libraries(chess raylib)

target_include_directories(chess PRIVATE
    "include/"
    "vendor/raylib/src/"
)

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})