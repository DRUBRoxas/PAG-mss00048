//
// Created by Manuel on 08/11/2024.
//

#ifndef SELECTORMODELO_H
#define SELECTORMODELO_H
#include <string>
#include <vector>
#include "imgui/imgui.h"

namespace PAG {
    class SelectorModelo {
    private:
        std::vector<std::string> modelos;
        int modeloSeleccionado = 0;
        int modeloBorrar = -1; //negativo para no cagarla
        int modeloCambiaModo = -1; //negativo para no cagarla

    public:
        void setModelos(std::vector<std::string> &nombres);

        void RefrescarSelectorModelo();

        int getModeloSeleccionado();

        int getModeloCambioModo();

        void setModeloSeleccionado(int modelo);

        int getModeloBorrar();

        void setModeloBorrar(int modelo);

        void setModeloCambiar(int i);

        SelectorModelo();

        ~SelectorModelo();
    };
} // PAG

#endif //SELECTORMODELO_H
