cmake_minimum_required(VERSION 3.15)

project(d3d8 LANGUAGES CXX)

add_library(d3d8 SHARED
    d3d8.cpp
)

set_target_properties(d3d8 PROPERTIES
    WINDOWS_EXPORT_ALL_SYMBOLS ON
)
