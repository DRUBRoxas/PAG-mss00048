//
// Created by Manuel on 19/12/2024.
//

#ifndef SELECTORLUCES_H
#define SELECTORLUCES_H
#include <string>
#include <vector>

namespace PAG {
    class SelectorLuces {
    private:
        std::vector<std::string> luces;
        int luzSeleccionada = 0;
        int luzBorrar = -1; //negativo para no cagarla
        int luzCambiaModo = -1; //negativo para no cagarla

    public:
        void setLuces(std::vector<std::string> nombres);

        void RefrescarSelectorLuces();

        int getLuzSeleccionada();

        int getLuzCambioModo();

        void setLuzSeleccionada(int luz);

        int getLuzBorrar();

        void setLuzBorrar(int luz);

        void setLuzCambiar(int i);

        SelectorLuces();

        ~SelectorLuces();
    };
}

#endif //SELECTORLUCES_H
