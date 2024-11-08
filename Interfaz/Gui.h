//
// Created by Manuel on 20/09/2024.
//

#ifndef GUI_H
#define GUI_H

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_opengl3_loader.h"

#include <GLFW/glfw3.h>

#include "ColorPicker.h"
#include "Consola.h"
#include "SelectorModelo.h"
#include "SelectorMovimiento.h"
#include "TextBox.h"
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
    TextBox* textBox;
    VentanaArchivos* ventanaArchivos;
    SelectorModelo* selectorModelo;
    virtual ~Gui();
    static Gui &getInstancia();
    void StartGui(GLFWwindow *window);
    void asignarCamara(Camera *camara);
    void EndGui();

    void RefrescarFrame();
};

} // PAG

#endif //GUI_H
