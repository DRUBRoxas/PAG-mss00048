//
// Created by Manuel on 25/09/2024.
//

#ifndef COLORPICKER_H
#define COLORPICKER_H
#include "imgui/imgui.h"

namespace PAG {

class ColorPicker {
private:
    ImVec4 color = ImVec4(1.0f, 0.0f, 0.0f, 1.0f); // Inicializado a rojo con opacidad completa
public:
    ColorPicker();
    ~ColorPicker();
    void RefrescarColorPicker();
};

} // PAG

#endif //COLORPICKER_H
