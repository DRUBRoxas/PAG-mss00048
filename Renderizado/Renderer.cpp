//
// Created by Manuel on 20/09/2024.
//

#include "Renderer.h"

namespace PAG {
    Renderer *Renderer::instancia = nullptr;
    //guardamos las coordenadas RGBA del color de fondo

    //Constructor por defecto
    Renderer::Renderer() {
        shaderProgram = nullptr;
    }


    //Destructor
    Renderer::~Renderer() {
        if (instancia) {
            delete instancia;
            instancia = nullptr;
        }
        if ( idVBO != 0 )
        { glDeleteBuffers ( 1, &idVBO );
        }
        if ( idIBO != 0 )
        { glDeleteBuffers ( 1, &idIBO );
        }
        if ( idVAO != 0 )
        { glDeleteVertexArrays ( 1, &idVAO );
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
        glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        if(shaderProgram != nullptr){
            glPolygonMode ( GL_FRONT_AND_BACK, GL_FILL );
            glUseProgram ( shaderProgram->getIdSP() );
            glBindVertexArray ( idVAO );
            glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER, idIBO );
            glDrawElements ( GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr );
        }
    }

    void Renderer::ResizeVentana(int ancho, int alto) {
        glViewport(0, 0, ancho, alto);
    }

    void Renderer::CambiarColorFondo(double red, double green, double blue, double alpha) {
        r=red;
        g=green;
        b=blue;
        a=alpha;
        glClearColor(r, g, b, a);
        std::string confirmacion="Color de fondo cambiado a: R: "+std::to_string(r)+" G: "+std::to_string(g)+" B: "+std::to_string(b)+" A: "+std::to_string(a);
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

    void Renderer::inicializaOpenGL() {
        glClearColor (r,g,b,a );
        glEnable ( GL_DEPTH_TEST );
        glEnable ( GL_MULTISAMPLE );
    }

    void PAG::Renderer::creaModeloEntrelazado() {
        GLfloat vertices[] = {
            // Positions        // Colors
            -0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
             0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
             0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f
        };

        GLuint indices[] = { 0, 1, 2 };

        glGenVertexArrays(1, &idVAO);
        glBindVertexArray(idVAO);

        glGenBuffers(1, &idVBO);
        glBindBuffer(GL_ARRAY_BUFFER, idVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);

        glGenBuffers(1, &idIBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idIBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    }

    void Renderer::enlazarShaderProgram(std::string nombreArchivo) {
        if(shaderProgram!=nullptr){
            delete shaderProgram;
            shaderProgram = nullptr;
        }
        shaderProgram = new ProgramShader();
        shaderProgram->ObtenShaders(nombreArchivo);
        creaModeloEntrelazado();
    }
} // PAG
