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

namespace PAG {

class Gui {
private:
    static Gui *instancia; ///< Instancia única de la clase
    Gui();
public:
    Consola* consola;
    ColorPicker* colorPicker;
    virtual ~Gui();
    static Gui &getInstancia();
    void StartGui(GLFWwindow *window);

    void EndGui();

    void RefrescarFrame();
};

} // PAG

#endif //GUI_H
