//
// Created by Manuel on 20/09/2024.
//

#ifndef GUI_H
#define GUI_H
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

namespace PAG {

class Gui {
private:
    static Gui *instancia; ///< Instancia única de la clase
    Gui();
public:
    virtual ~Gui();
    static Gui &getInstancia();
    void StartGui(GLFWwindow *window);
};

} // PAG

#endif //GUI_H
