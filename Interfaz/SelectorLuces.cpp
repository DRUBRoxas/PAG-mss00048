//
// Created by Manuel on 19/12/2024.
//
#include "imgui/imgui.h"
#include "SelectorLuces.h"
#include "../imfilebrowser.h"


namespace PAG {
    SelectorLuces::SelectorLuces() {
    }
    SelectorLuces::~SelectorLuces() {
    }

    void SelectorLuces::setLuces(std::vector<std::string>nombres) {
        luces=nombres;
    }

    void SelectorLuces::RefrescarSelectorLuces() {
        static int selected_item = -1;
        if (luces.empty()) {
            return; // No mostrar la ventana si no hay luces cargadas
        }

        if (ImGui::Begin("Selector de Luces")) {
            if (ImGui::BeginCombo("Selecciona una Luz", selected_item >= 0 ? luces[selected_item].c_str() : "Selecciona una luz")) {
                for (int i = 0; i < luces.size(); ++i) {
                    bool is_selected = (selected_item == i);
                    if (ImGui::Selectable(luces[i].c_str(), is_selected)) {
                        selected_item = i;
                        luzSeleccionada=i;
                    }
                    if (is_selected) {
                        ImGui::SetItemDefaultFocus(); // Para marcar el ítem seleccionado
                    }
                }
                ImGui::EndCombo();
            }
            if(ImGui::Button("Borrar Luz")) {
                luzBorrar=luzSeleccionada;
            }
            if (ImGui::Button("Apagar Luz")) {
                luzCambiaModo=luzSeleccionada;
            }
            ImGui::End();
        }
    }

    int SelectorLuces::getLuzSeleccionada() {
        if (luces.size()==0) {
            return -1;
        }
        return luzSeleccionada;
    }

    void SelectorLuces::setLuzSeleccionada(int luz) {
        luzSeleccionada=luz;
    }

    void SelectorLuces::setLuzBorrar(int luz) {
        luzBorrar=luz;
    }

    int SelectorLuces::getLuzBorrar() {
        return luzBorrar;
    }

    int SelectorLuces::getLuzCambioModo() {
        return luzCambiaModo;
    }

    void SelectorLuces::setLuzCambiar(int i) {
        luzCambiaModo=i;
    }


}
