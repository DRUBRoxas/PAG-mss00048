//
// Created by Manuel on 03/11/2024.
//

#include <glad/glad.h>
#include "assimp/postprocess.h"
#include "assimp/scene.h"
#include "Modelo.h"

namespace PAG {
    Modelo::Modelo(std::string ruta, std::string nombreShader) {
        shader_program = new ProgramShader();
        shader_program->ObtenShaders(nombreShader);
        //Guardar el nombre del modelo para su eliminación más adelante
        nombreModelo = ruta;
        cargarModelo(ruta);
    }
    Modelo::~Modelo() {
        if ( idVBO != 0 )
        { glDeleteBuffers ( 1, &idVBO );
        }
        if ( idIBO != 0 )
        { glDeleteBuffers ( 1, &idIBO );
        }
        if ( idVAO != 0 )
        { glDeleteVertexArrays ( 1, &idVAO );
        }
        if(shader_program!=nullptr){
            delete shader_program;
        }
    }

    GLuint* Modelo::get_id_vao() {
        return &idVAO;
    }

    GLuint* Modelo::get_id_vbo() {
        return &idVBO;
    }

    GLuint* Modelo::get_id_ibo() {
        return &idIBO;
    }

    void Modelo::cargarModelo(std::string ruta) {
        const aiScene *escena = importador.ReadFile(ruta, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_GenSmoothNormals);
        if (!escena || escena->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !escena->mRootNode) {
            return;
        }
        malla=escena->mMeshes[0];
    }

    std::vector<GLfloat> Modelo::getVertices() {
        std::vector<GLfloat> vertices;
        for (int i = 0; i < malla->mNumVertices; i++) {
            vertices.push_back(malla->mVertices[i].x);
            vertices.push_back(malla->mVertices[i].y);
            vertices.push_back(malla->mVertices[i].z);
        }
        return vertices;
    }

    std::vector<GLuint> Modelo::getIndices() {
        std::vector<GLuint> indices;
        for (int i = 0; i < malla->mNumFaces; i++) {
            for (int j=0; j<malla->mFaces[i].mNumIndices; j++) {
                indices.push_back(malla->mFaces[i].mIndices[j]);
            }
        }
        return indices;
    }

    std::vector<GLfloat> Modelo::getColores() {
        std::vector<GLfloat> colores;
        for (int i = 0; i < malla->mNumVertices; i++) {
            colores.push_back(malla->mNormals[i].x);
            colores.push_back(malla->mNormals[i].y);
            colores.push_back(malla->mNormals[i].z);
            colores.push_back(1.0);
        }
        return colores;
    }

    void Modelo::enlazarShaderProgram(std::string nombreArchivo) {
        if (shader_program != nullptr) {
            delete shader_program;
            shader_program = nullptr;
        }
        shader_program = new ProgramShader();
        shader_program->ObtenShaders(nombreArchivo);
        //creaModelos();
    }

    TipoVisualizacion Modelo::getTipoVisualizacion() {
        return tipoVisualizacion;
    }

    glm::vec3 Modelo::getColorDifuso() {
        return colorDifuso;
    }

    void Modelo::cambiaModoVisualizacion() {
        if (tipoVisualizacion == ALAMBRE) {
            tipoVisualizacion = RELLENO;
        } else {
            tipoVisualizacion = ALAMBRE;
        }
    }

    glm::vec3 Modelo::getColorAmbiental() {
        return colorAmbiental;
    }

    GLfloat Modelo::getShininess() {
        return shininess;
    }

    glm::vec3 Modelo::getColorEspecular() {
        return colorEspecular;
    }


} // PAG