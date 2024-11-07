#include "Renderer.h"

namespace PAG {
    Renderer *Renderer::instancia = nullptr;

    // Constructor por defecto
    Renderer::Renderer() {
        shaderProgram = nullptr;
        camara = Camera();
    }

    // Destructor
    Renderer::~Renderer() {
        if (instancia) {
            delete instancia;
            instancia = nullptr;
        }
        for (Modelo* modelo : modelos) {
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

    void Renderer::refrescar() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        if (shaderProgram != nullptr) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glUseProgram(shaderProgram->getIdSP());
            for (Modelo* modelo : modelos) {
                if (modelo && modelo->get_id_vao() && modelo->get_id_ibo()) {
                    // Crear la matriz MVP para el modelo actual
                    glm::mat4 mvp = camara.getProjectionMatrix() * camara.getViewMatrix() * modelo->getTransformacion();
                    glBindVertexArray(*modelo->get_id_vao());
                    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *modelo->get_id_ibo());
                    // Enviar la matriz MVP al shader
                    glUniformMatrix4fv(glGetUniformLocation(shaderProgram->getIdSP(), "matrizMVP"), 1, GL_FALSE, glm::value_ptr(mvp));
                    // Dibujar el modelo
                    glDrawElements(GL_TRIANGLES, modelo->malla->mNumFaces * 3, GL_UNSIGNED_INT, nullptr);
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
        std::string confirmacion = "Color de fondo cambiado a: R: " + std::to_string(r) + " G: " + std::to_string(g) + " B: " + std::to_string(b) + " A: " + std::to_string(a);
    }

    std::string Renderer::ObtenerDatos() {
        std::string renderer = reinterpret_cast<const char *>(glGetString(GL_RENDERER));
        std::string vendor = reinterpret_cast<const char *>(glGetString(GL_VENDOR));
        std::string version = reinterpret_cast<const char *>(glGetString(GL_VERSION));
        std::string shadingLanguageVersion = reinterpret_cast<const char *>(glGetString(GL_SHADING_LANGUAGE_VERSION));
        return "Renderer: " + renderer + "\nVendor: " + vendor + "\nVersion: " + version + "\nShading Language Version: " + shadingLanguageVersion;
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
    }

    void Renderer::enlazarShaderProgram(std::string nombreArchivo) {
        if (shaderProgram != nullptr) {
            delete shaderProgram;
            shaderProgram = nullptr;
        }
        shaderProgram = new ProgramShader();
        shaderProgram->ObtenShaders(nombreArchivo);
        creaModelos();
    }

    void Renderer::setCamera(const Camera& camera) {
        this->viewMatrix = camera.getViewMatrix();
        this->projectionMatrix = camera.getProjectionMatrix();
    }

    Camera Renderer::getCamara() {
        return camara;
    }

    void Renderer::borraModelo(std::string ruta) {
    auto it = std::remove_if(modelos.begin(), modelos.end(), [&ruta](Modelo* modelo) {
        if (modelo->nombreModelo == ruta) {
            delete modelo;
            return true;
        }
        return false;
    });
    modelos.erase(it, modelos.end());
}
    // Función para crear múltiples modelos
    void Renderer::creaModelos() {
        int posicion=modelos.size()-1;
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

                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
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
    }// PAG