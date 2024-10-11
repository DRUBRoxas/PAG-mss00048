cmake_minimum_required(VERSION 3.29)
project(PruebaGraficas)
# First, tell CMake to find the package.
# Conan will install the packages so that CMake can find it:

find_package(glad)
find_package(glfw3)
file( GLOB IMGUI imgui/*cpp)
# Then, link your executable or library with the corresponding package targets:
add_executable(PruebaGraficas main.cpp
        Renderer.cpp
        ${IMGUI}
        gui.cpp
        gui.h
        Consola.cpp
        Consola.h
        ColorPicker.cpp
        ColorPicker.h
        ProgramShader.cpp
        ProgramShader.h
        textbox.cpp
        textbox.h)

target_link_libraries(PruebaGraficas glad::glad)
target_link_libraries(PruebaGraficas glfw)

set(CMAKE_CXX_STANDARD 20)

