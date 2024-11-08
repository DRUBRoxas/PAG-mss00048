//
// Created by Manuel on 20/09/2024.
//

#include "Gui.h"

namespace PAG {
    Gui *Gui::instancia = nullptr;
    Gui::Gui() {
        consola = new Consola;
        colorPicker = new ColorPicker;
        textBox = new TextBox;
        selectorMovimiento= new SelectorMovimiento;
        ventanaArchivos = new VentanaArchivos;
        selectorModelo = new SelectorModelo;
        transformadorModelo = new TransformadorModelo;
    }

    Gui::~Gui() {
        delete consola;
        delete instancia;
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
        ImGui_ImplGlfw_InitForOpenGL ( window, true );
        ImGui_ImplOpenGL3_Init ();
    }

    void Gui::EndGui() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void Gui::RefrescarFrame() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        // Se dibujan los controles de Dear ImGui
        consola->RefrescarConsola();
        colorPicker->RefrescarColorPicker();
        textBox->RefrescarTextBox();
        selectorMovimiento->RefrescarSelector();
        ventanaArchivos->RefrescarVentanaArchivos();
        selectorModelo->RefrescarSelectorModelo();
        transformadorModelo->RefrescarTransformadorModelo();
        // Aquí va el dibujado de la escena con instrucciones OpenGL
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData ( ImGui::GetDrawData() );
    }

    void Gui::asignarCamara(Camera *camara) {
        selectorMovimiento->setCamera(camara);
    }

} // PAG