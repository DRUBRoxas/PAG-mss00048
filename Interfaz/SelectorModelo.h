//
// Created by Manuel on 08/11/2024.
//

#ifndef SELECTORMODELO_H
#define SELECTORMODELO_H
#include <string>
#include <vector>

namespace PAG {

class SelectorModelo {
private:
    std::vector<std::string> modelos;
    int modeloSeleccionado=0;
    int modeloBorrar=-1; //negativo para no cagarla
public:
    void setModelos(std::vector<std::string> &nombres);
    void RefrescarSelectorModelo();
    int getModeloSeleccionado();

    void setModeloSeleccionado(int modelo);

    int getModeloBorrar();

    void setModeloBorrar(int modelo);

    SelectorModelo();
    ~SelectorModelo();

};

} // PAG

#endif //SELECTORMODELO_H
