//
// Created by Manuel on 25/09/2024.
//

#include "ColorPicker.h"
#include "Renderer.h"
#include "Gui.h"
#include "imgui/imgui.h"

namespace PAG {
    ColorPicker::ColorPicker() {
    }

    ColorPicker::~ColorPicker() {
    }

    void ColorPicker::RefrescarColorPicker() {
        ImGui::Begin("Color Picker");
        static ImVec4 colorAnterior = color;
        if (ImGui::ColorPicker4("Color Picker", (float*)&color, ImGuiColorEditFlags_PickerHueWheel)) {
            if (color.x != colorAnterior.x || color.y != colorAnterior.y || color.z != colorAnterior.z || color.w != colorAnterior.w) {
                std::string confirmacion = PAG::Renderer::getInstancia().CambiarColorFondo(color.x, color.y, color.z, color.w);
                PAG::Gui::getInstancia().consola->NuevoMensaje(confirmacion);
                colorAnterior = color;
            }
        }
        ImGui::End();
    }

} // PAG