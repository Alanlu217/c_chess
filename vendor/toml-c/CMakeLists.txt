cmake_minimum_required(VERSION 3.28)
project(toml-c)

add_library(toml-c toml.c)
target_include_directories(toml-c PUBLIC .)