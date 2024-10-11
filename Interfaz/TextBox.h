//
// Created by Manuel on 10/10/2024.
//

#ifndef TEXTBOX_H
#define TEXTBOX_H
#include <string>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_opengl3_loader.h"
#include "imgui/imgui_stdlib.h"


namespace PAG {

class TextBox {
private:
    bool _buttonPressed;
    std::string name="";

public:
    TextBox();

    ~TextBox();

    void SetPosicion(int x, int y);

    void SetSize(int x, int y);

    void SetWindowFontScale(float scale);

    void RefrescarTextBox();

};

} // PAG

#endif //TEXTBOX_H
