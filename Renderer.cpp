//
// Created by Manuel on 20/09/2024.
//

#include "Renderer.h"
#include <iostream>

#include "Consola.h"

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

        if ( idVS != 0 )
        { glDeleteShader ( idVS );
        }
        if ( idFS != 0 )
        { glDeleteShader ( idFS );
        }
        if ( idSP != 0 )
        { glDeleteProgram ( idSP );
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
        glPolygonMode ( GL_FRONT_AND_BACK, GL_FILL );
        glUseProgram ( idSP );
        glBindVertexArray ( idVAO );
        glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER, idIBO );
        glDrawElements ( GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr );
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

    /**
    * Método para crear, compilar y enlazar el shader program
    * @note No se incluye ninguna comprobación de errores
    */
    void PAG::Renderer::creaShaderProgram( )
    {
        std::string miVertexShader =
        "#version 410\n"
        "layout (location = 0) in vec3 posicion;\n"
        "void main ()\n"
        "{ gl_Position = vec4 ( posicion, 1 );\n"
        "}\n";
        std::string miFragmentShader =
        "#version 410\n"
        "out vec4 colorFragmento;\n"
        "void main ()\n"
        "{ colorFragmento = vec4 ( 1.0, .4, .2, 1.0 );\n"
        "}\n";
        idVS = glCreateShader ( GL_VERTEX_SHADER );
        const GLchar* fuenteVS = miVertexShader.c_str ();
        glShaderSource ( idVS, 1, &fuenteVS, nullptr );
        glCompileShader ( idVS );
        idFS = glCreateShader ( GL_FRAGMENT_SHADER );
        const GLchar* fuenteFS = miFragmentShader.c_str ();
        glShaderSource ( idFS, 1, &fuenteFS, nullptr );
        glCompileShader ( idFS );
        idSP = glCreateProgram ();
        glAttachShader ( idSP, idVS );
        glAttachShader ( idSP, idFS );
        glLinkProgram ( idSP );
    }

    /**
    * Método para crear el VAO para el modelo a renderizar
    * @note No se incluye ninguna comprobación de errores
    */
    void PAG::Renderer::creaModelo ( )
    { GLfloat vertices[] = {-.5,-.5, 0,
    .5,-.5, 0,
    .0, .5, 0 };
        GLuint indices[] = { 0, 1, 2 };
        glGenVertexArrays ( 1, &idVAO );
        glBindVertexArray ( idVAO );
       glGenBuffers ( 1, &idVBO );
        glBindBuffer ( GL_ARRAY_BUFFER, idVBO );
        glBufferData ( GL_ARRAY_BUFFER, 9*sizeof(GLfloat), vertices,
        GL_STATIC_DRAW );
        glVertexAttribPointer ( 0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat),
        nullptr );
        glEnableVertexAttribArray ( 0 );
        glGenBuffers ( 1, &idIBO );
        glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER, idIBO );
        glBufferData ( GL_ELEMENT_ARRAY_BUFFER, 3*sizeof(GLuint), indices,
        GL_STATIC_DRAW );
    }

} // PAG
