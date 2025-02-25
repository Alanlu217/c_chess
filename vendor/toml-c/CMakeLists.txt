cmake_minimum_required(VERSION 3.30)
project(toml-c)

add_library(toml-c toml.c)
target_include_directories(toml-c PUBLIC .)