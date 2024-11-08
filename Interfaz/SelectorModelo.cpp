//
// Created by Manuel on 08/11/2024.
//

#include "SelectorModelo.h"

#include "imgui/imgui.h"

namespace PAG {
    SelectorModelo::SelectorModelo() {
    }
    SelectorModelo::~SelectorModelo() {
    }
    void SelectorModelo::setModelos(std::vector<std::string>& nombres) {
        modelos=nombres;
    }

    void SelectorModelo::RefrescarSelectorModelo() {
        static int selected_item = -1;
        if (ImGui::Begin("Selector de Modelos")) {
            if (ImGui::BeginCombo("Selecciona un Modelo", selected_item >= 0 ? modelos[selected_item].c_str() : "Selecciona un modelo")) {
                for (int i = 0; i < modelos.size(); ++i) {
                    bool is_selected = (selected_item == i);
                    if (ImGui::Selectable(modelos[i].c_str(), is_selected)) {
                        selected_item = i;
                        modeloSeleccionado=i;
                    }
                    if (is_selected) {
                        ImGui::SetItemDefaultFocus(); // Para marcar el ítem seleccionado
                    }
                }
                ImGui::EndCombo();
            }
            ImGui::End();
        }

    }

    int SelectorModelo::getModeloSeleccionado() {
        return modeloSeleccionado;
    }

    void SelectorModelo::setModeloSeleccionado(int modelo) {
        modeloSeleccionado=modelo;
    }

} // PAG