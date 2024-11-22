//
// Created by Manuel on 03/11/2024.
//

#ifndef MODELADO_H
#define MODELADO_H
#include <string>
#include <vector>
#include "assimp/Importer.hpp"
#include "assimp/mesh.h"
#include "glm/glm.hpp"
#include "Visualizacion.h"
#include "../Renderizado/ProgramShader.h"
#include "../Renderizado/Shader.h"
namespace PAG {
    class Modelo {
public:
    std::string nombreModelo;
    Assimp::Importer importador;
    aiMesh *malla=nullptr;
    ProgramShader* shader_program;
    Modelo(std::string ruta);
    void Dibujar(Shader &shader);

    TipoVisualizacion getTipoVisualizacion();

    glm::vec4 getColorDifuso();

    void cambiaModoVisualizacion();

    Modelo(std::string ruta, std::string nombreShader);

    ~Modelo();
    GLuint* get_id_vao();
    GLuint* get_id_vbo();
    GLuint* get_id_ibo();
    std::vector<GLfloat> getVertices();
    std::vector<GLuint> getIndices();
    std::vector<GLfloat> getColores();

    void enlazarShaderProgram(std::string nombreArchivo);

    // Nueva función para obtener y modificar la matriz de transformación
    glm::mat4 getTransformacion() const { return transformacion; }
    void setTransformacion(const glm::mat4& t) { transformacion = t; }

    ProgramShader* getShaderProgram() { return shader_program; }

private:
    std::string directorio;
    GLuint idVAO = 0; // Identificador del vertex array object
    GLuint idVBO = 0; // Identificador del vertex buffer object
    GLuint idIBO = 0; // Identificador del index buffer object
    glm::mat4 transformacion = glm::mat4(1.0f);
    void cargarModelo(std::string ruta);

    // Tipo de visualización
    TipoVisualizacion tipoVisualizacion = ALAMBRE;
    // Materiales
    glm::vec4 colorAmbiental;
    glm::vec4 colorDifuso=glm::vec4(0.5f, 0.3f, 0.1f, 1.0f);
    glm::vec4 colorEspecular;
    glm::vec4 exponeneteEspecular;
};

} // PAG

#endif //MODELADO_H
