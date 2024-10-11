//
// Created by Manuel on 10/10/2024.
//
#include "Renderer.h"
#include "TextBox.h"

#include "Gui.h"


namespace PAG {
    TextBox::TextBox() {
    }

    TextBox::~TextBox() {
    }

    void TextBox::SetPosicion(int x, int y) {
        ImGui::SetWindowPos(ImVec2(x, y), ImGuiCond_Once);
    }

    void TextBox::SetSize(int x, int y) {
        ImGui::SetWindowSize(ImVec2(x, y), ImGuiCond_Once);
    }

    void TextBox::SetWindowFontScale(float scale) {
        ImGui::SetWindowFontScale(scale);
    }

    void TextBox::RefrescarTextBox() {
        ImGui::SetNextWindowPos(ImVec2(100, 400), ImGuiCond_Once);
        ImGui::SetNextWindowSize(ImVec2(200, 75), ImGuiCond_Once);
        if (ImGui::Begin("SeleccionadorShaderProgram")) {
            // La ventana está desplegada
            ImGui::SetWindowFontScale(1.0f); // Escalamos el texto si fuera necesario
            ImGui::InputText("##", &name, ImGuiInputTextFlags_AutoSelectAll);

            _buttonPressed = ImGui::Button("Load");


        }
        ImGui::End();
        if(_buttonPressed) {
            try {
                Renderer::getInstancia().enlazarShaderProgram(name);
                name="";
            }catch (std::runtime_error &e) {
                Gui::getInstancia().consola->NuevoMensaje(e.what());
                name="";
            }

        }
    }
} // PAG