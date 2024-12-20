//
// Created by Manuel on 08/11/2024.
//

#include "imgui/imgui.h"
#include "imgui/imgui_stdlib.h"
#include "VentanaArchivos.h"

#include <iostream>

#include "Gui.h"

namespace PAG{
    VentanaArchivos::VentanaArchivos() {
        fileDialog.SetTitle("Seleccione un archivo");
        fileDialog.SetTypeFilters({ ".obj" });
    }

    VentanaArchivos::~VentanaArchivos() {
    }

    void VentanaArchivos::RefrescarVentanaArchivos() {
        if(ImGui::Begin("Carga de Modelos")) {
            // Campo de texto para ingresar el nombre del shader
            ImGui::SetWindowFontScale(1.0f);
            ImGui::InputText("##", &shaderName, ImGuiInputTextFlags_AutoSelectAll);

            // Botón para abrir la ventana de archivos
            if(ImGui::Button("Abrir ventana de archivos")) {
                fileDialog.Open();
            }

            _buttonPressed = ImGui::Button("Confirmar");
        }
        ImGui::End();

        fileDialog.Display();

        if (fileDialog.HasSelected()) {
            path = fileDialog.GetSelected().string();
            fileDialog.ClearSelected();
        }
        if(_buttonPressed) {
            if(path.empty() || shaderName.empty()) {
                if (shaderName.empty()) {
                    Gui::getInstancia().consola->NuevoMensaje("No se ha seleccionado un shader");
                }
                if (path.empty()) {
                    Gui::getInstancia().consola->NuevoMensaje("No se ha seleccionado un archivo");
                }
                cambiosRealizados = false;
            } else {
                cambiosRealizados = true;
            }
        }
    }

    void VentanaArchivos::ClearPath() {
        path = "";
    }

    std::string VentanaArchivos::getPath() {
        return path;
    }

    std::string VentanaArchivos::getShaderName() {
        return shaderName;
    }


}
