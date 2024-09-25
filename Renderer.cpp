//
// Created by Manuel on 20/09/2024.
//

#include "Renderer.h"
#include <iostream>
namespace PAG {
    Renderer *Renderer::instancia = nullptr;
    //guardamos las coordenadas RGBA del color de fondo

    //Constructor por defecto
    Renderer::Renderer() {
    }

    //Destructor
    Renderer::~Renderer() {
        if (instancia) {
            delete instancia;
            instancia = nullptr;
        }
    }

    //Devuelve la dirección de memoria del objeto
    Renderer &Renderer::getInstancia() {
        if (!instancia) {
            instancia = new Renderer;
        }
        return *instancia;
    }

    //Método que hace el refresco de la escena
    void Renderer::refrescar() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Renderer::ResizeVentana(int ancho, int alto) {
        glViewport(0, 0, ancho, alto);
    }

    std::string Renderer::CambiarColorFondo(double red, double green, double blue, double alpha) {
        r=red;
        g=green;
        b=blue;
        a=alpha;
        glClearColor(r, g, b, a);
        std::string confirmacion="Color de fondo cambiado a: R: "+std::to_string(r)+" G: "+std::to_string(g)+" B: "+std::to_string(b)+" A: "+std::to_string(a);
        return confirmacion;
    }

    std::string Renderer::ObtenerDatos() {
        std::string renderer = reinterpret_cast<const char *>(glGetString(GL_RENDERER));
        std::string vendor = reinterpret_cast<const char *>(glGetString(GL_VENDOR));
        std::string version = reinterpret_cast<const char *>(glGetString(GL_VERSION));
        std::string shadingLanguageVersion = reinterpret_cast<const char *>(glGetString(GL_SHADING_LANGUAGE_VERSION));
        return "Renderer: " + renderer + "\nVendor: " + vendor + "\nVersion: " + version +
               "\nShading Language Version: " + shadingLanguageVersion;
    }

    void Renderer::ActivarProfundidad() {
        glEnable(GL_DEPTH_TEST);
    }

    void Renderer::DesactivarProfundidad() {
        glDisable(GL_DEPTH_TEST);
    }

} // PAG
