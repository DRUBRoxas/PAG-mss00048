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
        camara = Camera();
        modelo = new Modelo("./Modelos/Panther.obj");
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
        glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        if(shaderProgram != nullptr){
            glPolygonMode ( GL_FRONT_AND_BACK, GL_FILL );
            glUseProgram ( shaderProgram->getIdSP() );
            glBindVertexArray ( *modelo->get_id_vao() );
            glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER, *modelo->get_id_ibo() );
            glUniformMatrix4fv ( glGetUniformLocation ( shaderProgram->getIdSP(), "matrizMVP" ), 1, GL_FALSE, glm::value_ptr(camara.getMVP()) );
            glDrawElements ( GL_TRIANGLES, modelo->malla->mNumFaces*3, GL_UNSIGNED_INT, nullptr);
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

    // void PAG::Renderer::creaModeloEntrelazado() {
    //     GLfloat vertices[] = {
    //         // Positions        // Colors
    //         -0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
    //          0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
    //          0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f
    //     };
    //
    //     GLuint indices[] = { 0, 1, 2 };
    //
    //     glGenVertexArrays(1, &idVAO);
    //     glBindVertexArray(idVAO);
    //
    //     glGenBuffers(1, &idVBO);
    //     glBindBuffer(GL_ARRAY_BUFFER, idVBO);
    //     glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    //
    //     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
    //     glEnableVertexAttribArray(0);
    //
    //     glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    //     glEnableVertexAttribArray(1);
    //
    //     glGenBuffers(1, &idIBO);
    //     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idIBO);
    //     glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    // }

    void Renderer::enlazarShaderProgram(std::string nombreArchivo) {
        if(shaderProgram!=nullptr){
            delete shaderProgram;
            shaderProgram = nullptr;
        }
        shaderProgram = new ProgramShader();
        shaderProgram->ObtenShaders(nombreArchivo);
        creaModelo();
    }

    void Renderer::setCamera(const Camera& camera) {
        this->viewMatrix = camera.getViewMatrix();
        this->projectionMatrix = camera.getProjectionMatrix();
    }

    Camera Renderer::getCamara() {
        return camara;
    }

    void PAG::Renderer::creaModelo() {
        std::vector <GLfloat> vertices = modelo->getVertices();
        std::vector <GLuint> indices = modelo->getIndices();
        std::vector <GLfloat> colores = modelo->getColores();

        glGenVertexArrays(1, modelo->get_id_vao());
        glBindVertexArray(*modelo->get_id_vao());

        glGenBuffers(1, modelo->get_id_vbo());
        glBindBuffer(GL_ARRAY_BUFFER, *modelo->get_id_vbo());
        glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
        glEnableVertexAttribArray(0);

        //Color
        GLuint colorVBO;
        glGenBuffers(1, &colorVBO);
        glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
        glBufferData(GL_ARRAY_BUFFER, colores.size()*sizeof(GLfloat), colores.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4*sizeof(GLfloat), nullptr);
        glEnableVertexAttribArray(1);


        glGenBuffers(1, modelo->get_id_ibo());
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *modelo->get_id_ibo());
        //Puede fallar aquí
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
    }
} // PAG
