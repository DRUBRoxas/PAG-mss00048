cmake_minimum_required(VERSION 3.29)
project(PruebaGraficas)
# First, tell CMake to find the package.
# Conan will install the packages so that CMake can find it:

find_package(glad)
find_package(glfw3)
find_package(glm)
file( GLOB IMGUI Interfaz/imgui/*cpp)
# Then, link your executable or library with the corresponding package targets:
add_executable(PruebaGraficas main.cpp
        Renderizado/Renderer.cpp
        ${IMGUI}
        Interfaz/Gui.cpp
        Interfaz/Gui.h
        Interfaz/Consola.cpp
        Interfaz/Consola.h
        Interfaz/ColorPicker.cpp
        Interfaz/ColorPicker.h
        Renderizado/ProgramShader.cpp
        Renderizado/ProgramShader.h
        Interfaz/TextBox.cpp
        Interfaz/TextBox.h
        Renderizado/Shader.cpp
        Renderizado/Shader.h
        Camera.cpp
        Camera.h
        Interfaz/SelectorMovimiento.cpp
        Interfaz/SelectorMovimiento.h
        Interfaz/Movimiento.h)

target_link_libraries(PruebaGraficas glad::glad)
target_link_libraries(PruebaGraficas glfw)
target_link_libraries(PruebaGraficas glm::glm)

set(CMAKE_CXX_STANDARD 20)

