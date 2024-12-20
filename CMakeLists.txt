cmake_minimum_required(VERSION 3.29)
project(PruebaGraficas)
# First, tell CMake to find the package.
# Conan will install the packages so that CMake can find it:
find_package(glfw3)
find_package(glm)
add_subdirectory(assimp)
#find_package(assimp CONFIG REQUIRED)
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
        Renderizado/Shader.cpp
        Renderizado/Shader.h
        Camera.cpp
        Camera.h
        Interfaz/SelectorMovimiento.cpp
        Interfaz/SelectorMovimiento.h
        Modelado/Modelo.cpp
        Modelado/Modelo.h
        Interfaz/VentanaArchivos.cpp
        Interfaz/VentanaArchivos.h
        imfilebrowser.h
        Interfaz/SelectorModelo.cpp
        Interfaz/SelectorModelo.h
        Interfaz/TransformadorModelo.cpp
        Interfaz/TransformadorModelo.h
        Modelado/Visualizacion.h
        glad/src/glad.c
        Renderizado/Luz.cpp
        Renderizado/Luz.h
        Interfaz/SelectorLuces.cpp
        Interfaz/SelectorLuces.h
)
link_directories("./assimp/lib")
target_link_libraries(PruebaGraficas glfw "-static")
target_link_libraries(PruebaGraficas glm::glm "-static")
target_link_libraries(PruebaGraficas assimp::assimp "-static")
target_include_directories(PruebaGraficas PUBLIC glad/include)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(ASSIMP_DLL_PATH "${CMAKE_SOURCE_DIR}/biblioteca")

# Copy the DLLs to the build directory
add_custom_command(TARGET PruebaGraficas POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${ASSIMP_DLL_PATH}/libassimp-5d.dll"
    $<TARGET_FILE_DIR:PruebaGraficas>)