//
// Created by Manuel on 20/09/2024.
//

#ifndef GUI_H
#define GUI_H

#include "ColorPicker.h"
#include "Consola.h"
#include "SelectorLuces.h"
#include "SelectorModelo.h"
#include "SelectorMovimiento.h"
#include "TransformadorModelo.h"
#include "VentanaArchivos.h"

namespace PAG {
    class TextBox;

    class Gui {
private:
    static Gui *instancia; ///< Instancia única de la clase
    Gui();
public:
    SelectorMovimiento* selectorMovimiento;
    Consola* consola;
    ColorPicker* colorPicker;
    VentanaArchivos* ventanaArchivos;
    SelectorModelo* selectorModelo;
    SelectorLuces* selectorLuces;
    TransformadorModelo* transformadorModelo;
    virtual ~Gui();
    static Gui &getInstancia();
    void StartGui(GLFWwindow *window);
    void asignarCamara(Camera *camara);
    void EndGui();

    void RefrescarFrame();
};

} // PAG

#endif //GUI_H
