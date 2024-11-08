//
// Created by Manuel on 08/11/2024.
//

#include "VentanaArchivos.h"

namespace PAG{
    VentanaArchivos::VentanaArchivos() {
        fileDialog.SetTitle("Seleccione un archivo");
        fileDialog.SetTypeFilters({ ".obj" });
    }

    VentanaArchivos::~VentanaArchivos() {
    }

    void VentanaArchivos::RefrescarVentanaArchivos() {
        if(ImGui::Begin("Carga de Modelos"))
        {
            // open file dialog when user clicks this button
            if(ImGui::Button("Abrir ventana de archivos"))
                fileDialog.Open();
        }ImGui::End();

        fileDialog.Display();

        if (fileDialog.HasSelected()) {
            path = fileDialog.GetSelected().string();
            fileDialog.ClearSelected();
        }
    }

    std::string VentanaArchivos::getPath() {
        return path;
    }

    void VentanaArchivos::ClearPath() {
        path = "";
    }
}