//
// Created by Manuel on 08/11/2024.
//

#ifndef VENTANAARCHIVOS_H
#define VENTANAARCHIVOS_H
#include "imgui/imgui.h"
#include "../imfilebrowser.h"
#include <string>
namespace PAG {
    class VentanaArchivos {
    public:
        VentanaArchivos();
        ~VentanaArchivos();

        void RefrescarVentanaArchivos();

        std::string getPath();

        void ClearPath();

    private:
        ImGui::FileBrowser fileDialog;
        std::string path="";
    };
}


#endif //VENTANAARCHIVOS_H
