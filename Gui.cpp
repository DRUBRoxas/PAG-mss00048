//
// Created by Manuel on 20/09/2024.
//

#include "Gui.h"

namespace PAG {
    Gui *Gui::instancia = nullptr;

    Gui::Gui() {
    }

    Gui::~Gui() {
    }

    Gui &Gui::getInstancia() {
        if (!instancia) {
            instancia = new Gui;
        }
        return *instancia;
    }

    void Gui::StartGui(GLFWwindow *window) {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext ();
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

        // Aquí w es el puntero a la ventana GLFW (GLFWwindow*)
        ImGui_ImplGlfw_InitForOpenGL (window, true );
        ImGui_ImplOpenGL3_Init ();
    }




} // PAG