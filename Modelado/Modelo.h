//
// Created by Manuel on 03/11/2024.
//

#ifndef MODELADO_H
#define MODELADO_H
#include <string>
#include <./assimp/Importer.hpp>
#include <./assimp/scene.h>
#include <./assimp/postprocess.h>
#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <GL/gl.h>
#include <glm/glm.hpp>

namespace PAG {
    class Shader;

    class Modelo {
public:
    std::string nombreModelo;
    Assimp::Importer importador;
    aiMesh *malla=nullptr;
    Modelo(std::string ruta);
    void Dibujar(Shader &shader);
    ~Modelo();

    GLuint* get_id_vao();

    GLuint* get_id_vbo();

    GLuint* get_id_ibo();

    std::vector<GLfloat> getVertices();
    std::vector<GLuint> getIndices();
    std::vector<GLfloat> getColores();
    // Nueva función para obtener y modificar la matriz de transformación
    glm::mat4 getTransformacion() const { return transformacion; }
    void setTransformacion(const glm::mat4& t) { transformacion = t; }

private:
    std::string directorio;
    GLuint idVAO = 0; // Identificador del vertex array object
    GLuint idVBO = 0; // Identificador del vertex buffer object
    GLuint idIBO = 0; // Identificador del index buffer object
    glm::mat4 transformacion = glm::mat4(1.0f);
    void cargarModelo(std::string ruta);

};

} // PAG

#endif //MODELADO_H
