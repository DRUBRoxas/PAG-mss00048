//
// Created by Manuel on 25/09/2024.
//

#include "Consola.h"


namespace PAG {
    Consola::Consola() {
    }

    Consola::~Consola() {
    }

    void Consola::SetPosicion(int x, int y) {
        ImGui::SetNextWindowPos(ImVec2(x, y), ImGuiCond_Once);
    }

    void Consola::SetSize(int x, int y) {
        ImGui::SetNextWindowSize(ImVec2(x, y), ImGuiCond_Once);
    }

    void Consola::SetWindowFontScale(float scale) {
        ImGui::SetWindowFontScale(scale);
    }

    void Consola::RefrescarConsola() {
        SetPosicion(10,10);
        if(ImGui::Begin("Consola")) {
            //Ventana Desplegada
            Consola::SetWindowFontScale(1.0f);
            for(int i=0; i<mensajes.size(); i++) {
                ImGui::TextUnformatted(mensajes[i].c_str());
            }

            if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY()) {
                ImGui::SetScrollHereY(1.0f);
            }
        }

        // Si la ventana no está desplegada, Begin devuelve false
        ImGui::End ();
    }

    void Consola::NuevoMensaje(std::string mensaje) {
        if(mensajes.size()>100) {
            mensajes.erase(mensajes.begin());
        }
        mensajes.push_back(mensaje);
    }
} // PAG