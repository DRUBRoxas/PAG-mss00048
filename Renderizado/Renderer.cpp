#include <glad/glad.h>
#include "Renderer.h"
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

namespace PAG {
    Renderer *Renderer::instancia = nullptr;

    // Constructor por defecto
    Renderer::Renderer() {
        camara = Camera();
        luces.push_back(Luz(TipoLuz::PUNTUAL));
        luces.push_back(Luz(TipoLuz::AMBIENTE));
        luces.push_back(Luz(TipoLuz::DIRECCIONAL));
        luces.push_back(Luz(TipoLuz::FOCO));
        luces[0].inicializarPuntual(glm::vec3(0.5f, 0.3f, 0.1f), glm::vec3(0.5f, 0.5f, 0.5f),
                                    glm::vec3(1.0f, 1.0f, 3.0f));
        luces[1].inicializarAmbiente(glm::vec3(0.0f, 0.0f, 1.0f));
        luces[2].inicializarDireccional(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.5f, 0.3f, 0.1f),
                                        glm::vec3(0.5f, 0.5f, 0.5f));
        luces[0].inicializarFoco(glm::vec3(0.0f, 3.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f),
                                 glm::vec3(1.0f, 0.0f, 0.0f), 5.0f, 2.0f);
    }

    // Destructor
    Renderer::~Renderer() {
        if (instancia) {
            delete instancia;
            instancia = nullptr;
        }
        for (Modelo *modelo: modelos) {
            delete modelo;
        }
        modelos.clear();
    }

    // Devuelve la dirección de memoria del objeto
    Renderer &Renderer::getInstancia() {
        if (!instancia) {
            instancia = new Renderer;
        }
        return *instancia;
    }

    // Renderer.cpp

    void setSubroutine(GLuint shaderProgram, const std::string &subroutineName, GLenum shaderType) {
        GLuint subroutineIndex = glGetSubroutineIndex(shaderProgram, shaderType, subroutineName.c_str());
        glUniformSubroutinesuiv(shaderType, 1, &subroutineIndex);
    }

    void Renderer::refrescar() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        for (Modelo *modelo: modelos) {
            bool primeraLuz = true;
            for (int i = 0; i < luces.size(); i++) {
                if (luces[i].isEncendida()) {
                    if (primeraLuz) {
                        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                        primeraLuz = false;
                    } else {
                        glBlendFunc(GL_SRC_ALPHA, GL_ONE);
                    }
                    if (modelo && modelo->get_id_vao() && modelo->get_id_ibo()) {
                        if (modelo->getShaderProgram() != nullptr) {
                            bool modoAlambre = false;
                            if (modelo->getTipoVisualizacion() == RELLENO) {
                                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                            } else if (modelo->getTipoVisualizacion() == ALAMBRE) {
                                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                                modoAlambre = true;
                            }
                            glUseProgram(modelo->getShaderProgram()->getIdSP());

                            if (modoAlambre) {
                                setSubroutine(modelo->getShaderProgram()->getIdSP(), "sinLuces", GL_FRAGMENT_SHADER);
                            } else {
                                switch (luces[i].getTipo()) {
                                    case TipoLuz::AMBIENTE:
                                        setSubroutine(modelo->getShaderProgram()->getIdSP(), "ambiente",
                                                      GL_FRAGMENT_SHADER);
                                        glUniform3fv(
                                            glGetUniformLocation(modelo->getShaderProgram()->getIdSP(), "Ka"), 1,
                                            glm::value_ptr(modelo->getColorAmbiental()));
                                        glUniform3fv(
                                            glGetUniformLocation(modelo->getShaderProgram()->getIdSP(), "Ia"), 1,
                                            glm::value_ptr(luces[i].getColorAmbiente()));
                                        break;
                                    case TipoLuz::PUNTUAL:
                                        setSubroutine(modelo->getShaderProgram()->getIdSP(), "puntual",
                                                      GL_FRAGMENT_SHADER);
                                        glUniform3fv(
                                            glGetUniformLocation(modelo->getShaderProgram()->getIdSP(), "Kd"), 1,
                                            glm::value_ptr(modelo->getColorDifuso()));
                                        glUniform3fv(
                                            glGetUniformLocation(modelo->getShaderProgram()->getIdSP(), "Id"), 1,
                                            glm::value_ptr(luces[i].getColorDifuso()));
                                        glUniform3fv(
                                            glGetUniformLocation(modelo->getShaderProgram()->getIdSP(), "Ks"), 1,
                                            glm::value_ptr(modelo->getColorEspecular()));
                                        glUniform3fv(
                                            glGetUniformLocation(modelo->getShaderProgram()->getIdSP(), "Is"), 1,
                                            glm::value_ptr(luces[i].getColorEspecular()));
                                        glUniform3fv(
                                            glGetUniformLocation(modelo->getShaderProgram()->getIdSP(),
                                                                 "lightPosition"), 1,
                                            glm::value_ptr(glm::vec4(luces[i].getPosicion(), 1.0f)*camara.getViewMatrix()));
                                        glUniform1f(
                                            glGetUniformLocation(modelo->getShaderProgram()->getIdSP(), "shininess"),
                                            modelo->getShininess());
                                        break;
                                    case TipoLuz::DIRECCIONAL:
                                        setSubroutine(modelo->getShaderProgram()->getIdSP(), "puntual",
                                                      GL_FRAGMENT_SHADER);
                                        glUniform3fv(
                                            glGetUniformLocation(modelo->getShaderProgram()->getIdSP(), "Kd"), 1,
                                            glm::value_ptr(modelo->getColorDifuso()));
                                        glUniform3fv(
                                            glGetUniformLocation(modelo->getShaderProgram()->getIdSP(), "Id"), 1,
                                            glm::value_ptr(luces[i].getColorDifuso()));
                                        glUniform3fv(
                                            glGetUniformLocation(modelo->getShaderProgram()->getIdSP(), "Ks"), 1,
                                            glm::value_ptr(modelo->getColorEspecular()));
                                        glUniform3fv(
                                            glGetUniformLocation(modelo->getShaderProgram()->getIdSP(), "Is"), 1,
                                            glm::value_ptr(luces[i].getColorEspecular()));
                                        glUniform3fv(
                                            glGetUniformLocation(modelo->getShaderProgram()->getIdSP(),
                                                                 "lightDirection"), 1,
                                            glm::value_ptr(glm::vec4(luces[i].getDireccion(), 1.0f)*camara.getViewMatrix()));
                                        glUniform1f(
                                            glGetUniformLocation(modelo->getShaderProgram()->getIdSP(), "shininess"),
                                            modelo->getShininess());
                                        break;
                                    case TipoLuz::FOCO:
                                        setSubroutine(modelo->getShaderProgram()->getIdSP(), "puntual",
                                                      GL_FRAGMENT_SHADER);
                                        glUniform3fv(
                                            glGetUniformLocation(modelo->getShaderProgram()->getIdSP(), "Kd"), 1,
                                            glm::value_ptr(modelo->getColorDifuso()));
                                        glUniform3fv(
                                            glGetUniformLocation(modelo->getShaderProgram()->getIdSP(), "Id"), 1,
                                            glm::value_ptr(luces[i].getColorDifuso()));
                                        glUniform3fv(
                                            glGetUniformLocation(modelo->getShaderProgram()->getIdSP(), "Ks"), 1,
                                            glm::value_ptr(modelo->getColorEspecular()));
                                        glUniform3fv(
                                            glGetUniformLocation(modelo->getShaderProgram()->getIdSP(), "Is"), 1,
                                            glm::value_ptr(luces[i].getColorEspecular()));
                                        glUniform3fv(
                                            glGetUniformLocation(modelo->getShaderProgram()->getIdSP(),
                                                                 "lightPosition"), 1,
                                            glm::value_ptr(camara.getViewMatrix()*glm::vec4(luces[i].getPosicion(), 1.0f)));
                                        glUniform3fv(
                                            glGetUniformLocation(modelo->getShaderProgram()->getIdSP(),
                                                                 "lightDirection"), 1,
                                            glm::value_ptr(camara.getViewMatrix()*glm::vec4(luces[i].getDireccion(), 1.0f)));
                                        glUniform1f(
                                            glGetUniformLocation(modelo->getShaderProgram()->getIdSP(), "shininess"),
                                            modelo->getShininess());
                                        glUniform1f(
                                            glGetUniformLocation(modelo->getShaderProgram()->getIdSP(),
                                                                 "spotAngle"),
                                            luces[i].getGamma());
                                        break;
                                }
                            }
                            // Crear la matriz MVP para el modelo actual
                            glm::mat4 mvp = camara.getProjectionMatrix() * camara.getViewMatrix() * modelo->
                                            getTransformacion();
                            glBindVertexArray(*modelo->get_id_vao());
                            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *modelo->get_id_ibo());
                            // Enviar la matriz MVP al shader
                            glUniformMatrix4fv(glGetUniformLocation(modelo->getShaderProgram()->getIdSP(), "matrizMVP"),
                                               1,
                                               GL_FALSE, glm::value_ptr(mvp));
                            glUniformMatrix4fv(
                                glGetUniformLocation(modelo->getShaderProgram()->getIdSP(), "matrizTransformacion"), 1,
                                GL_FALSE, glm::value_ptr(modelo->getTransformacion()));
                            glUniformMatrix4fv(
                                glGetUniformLocation(modelo->getShaderProgram()->getIdSP(), "mModelView"), 1,
                                GL_FALSE, glm::value_ptr(camara.getViewMatrix()));
                            // Dibujar el modelo
                            glDrawElements(GL_TRIANGLES, modelo->malla->mNumFaces * 3, GL_UNSIGNED_INT, nullptr);
                        }
                    }
                }
            }
        }
    }


    void Renderer::ResizeVentana(int ancho, int alto) {
        glViewport(0, 0, ancho, alto);
    }

    void Renderer::CambiarColorFondo(double red, double green, double blue, double alpha) {
        r = red;
        g = green;
        b = blue;
        a = alpha;
        glClearColor(r, g, b, a);
        std::string confirmacion = "Color de fondo cambiado a: R: " + std::to_string(r) + " G: " + std::to_string(g) +
                                   " B: " + std::to_string(b) + " A: " + std::to_string(a);
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
        glClearColor(r, g, b, a);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_MULTISAMPLE);
        glEnable(GL_BLEND);
        glDepthFunc(GL_LEQUAL);
    }

    void Renderer::setCamera(const Camera &camera) {
        this->viewMatrix = camera.getViewMatrix();
        this->projectionMatrix = camera.getProjectionMatrix();
    }

    Camera Renderer::getCamara() {
        return camara;
    }

    void Renderer::borraModelo(int posicion) {
        if (posicion >= 0 && posicion < modelos.size()) {
            delete modelos[posicion];
            modelos.erase(modelos.begin() + posicion);
        }
    }

    void Renderer::borraLuz(int posicion) {
        if (posicion >= 0 && posicion < luces.size()) {
            luces.erase(luces.begin() + posicion);
        }
    }

    // Función para crear múltiples modelos
    void Renderer::creaModelos() {
        int posicion = modelos.size() - 1;
        if (posicion >= 0) {
            std::vector<GLfloat> vertices = modelos[posicion]->getVertices();
            std::vector<GLuint> indices = modelos[posicion]->getIndices();
            std::vector<GLfloat> colores = modelos[posicion]->getColores();

            glGenVertexArrays(1, modelos[posicion]->get_id_vao());
            glBindVertexArray(*modelos[posicion]->get_id_vao());
            std::cout << "ID VAO: " << *modelos[posicion]->get_id_vao() << std::endl;

            glGenBuffers(1, modelos[posicion]->get_id_vbo());
            glBindBuffer(GL_ARRAY_BUFFER, *modelos[posicion]->get_id_vbo());
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void *) 0);
            glEnableVertexAttribArray(0);

            // Color
            GLuint colorVBO;
            glGenBuffers(1, &colorVBO);
            glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
            glBufferData(GL_ARRAY_BUFFER, colores.size() * sizeof(GLfloat), colores.data(), GL_STATIC_DRAW);
            glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), nullptr);
            glEnableVertexAttribArray(1);

            glGenBuffers(1, modelos[posicion]->get_id_ibo());
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *modelos[posicion]->get_id_ibo());
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
        }
    }

    // Método para obtener los nombres de los modelos
    std::vector<std::string> Renderer::obtenerNombresModelos() {
        std::vector<std::string> nombres;
        for (Modelo *modelo: modelos) {
            nombres.push_back(modelo->nombreModelo);
        }
        return nombres;
    }

    std::vector<std::string> Renderer::obtenerNombresLuces() {
        std::vector<std::string> nombres;
        for (Luz luz: luces) {
            nombres.push_back(luz.getNombre());
        }
        return nombres;
    }


    void Renderer::cambiaModo(int modelo) {
        modelos[modelo]->cambiaModoVisualizacion();
    }

    void Renderer::EnciendeLuz(int luz) {
        luces[luz].CambioModoEncendido();
    }
} // PAG
