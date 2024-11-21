//
// Created by Manuel on 25/09/2024.
//
#ifndef CONSOLA_H
#define CONSOLA_H

#include <string>
#include <vector>

#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

namespace PAG {

class Consola {
private:
    std::vector<std::string> mensajes;
public:
    Consola();
    ~Consola();
    void SetPosicion(int x, int y);

    void SetWindowFontScale(float scale);

    void RefrescarConsola();

    void NuevoMensaje(std::string mensaje);
};

} // PAG

#endif //CONSOLA_H
