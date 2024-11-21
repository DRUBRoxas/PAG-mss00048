//
// Created by Manuel on 08/11/2024.
//

#ifndef VENTANAARCHIVOS_H
#define VENTANAARCHIVOS_H
#include "../imfilebrowser.h"
#include <string>
namespace PAG {
    class VentanaArchivos {
    public:
        bool cambiosRealizados=false;
        VentanaArchivos();
        ~VentanaArchivos();

        void RefrescarVentanaArchivos();

        std::string getPath();

        void ClearPath();
        std::string getShaderName();
    private:
        bool _buttonPressed;
        std::string shaderName="";
        ImGui::FileBrowser fileDialog;
        std::string path="";
    };
}


#endif //VENTANAARCHIVOS_H
