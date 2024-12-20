//
// Created by Manuel on 08/11/2024.
//

#include "SelectorModelo.h"


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
        if (modelos.empty()) {
            return; // No mostrar la ventana si no hay modelos cargados
        }
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
            if(ImGui::Button("Borrar Modelo")) {
                modeloBorrar=modeloSeleccionado;
            }
            if (ImGui::Button("Cambiar modo Visualización")) {
                modeloCambiaModo=modeloSeleccionado;
            }
            ImGui::End();
        }

    }

    int SelectorModelo::getModeloSeleccionado() {
        if (modelos.size()==0) {
            return -1;
        }
        return modeloSeleccionado;
    }

    void SelectorModelo::setModeloSeleccionado(int modelo) {
        modeloSeleccionado=modelo;
    }

    int SelectorModelo::getModeloBorrar() {
        return modeloBorrar;
    }

    void SelectorModelo::setModeloBorrar(int modelo) {
        modeloBorrar=modelo;
    }

   int SelectorModelo::getModeloCambioModo() {
       return modeloCambiaModo;
   }
    void SelectorModelo::setModeloCambiar(int i) {
        modeloCambiaModo=i;
    }

} // PAG