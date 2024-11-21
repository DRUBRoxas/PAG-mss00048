#ifndef TRANSFORMADOR_MODELO_H
#define TRANSFORMADOR_MODELO_H

#include <glm/glm.hpp>
#include <GL/gl.h>

namespace PAG {

    class TransformadorModelo {
    public:
        bool transformacionAplicada = false;
        TransformadorModelo();
        ~TransformadorModelo();

        glm::mat4 actualizarTransformacion();
        void RefrescarTransformadorModelo();
        glm::mat4 getTransformacion();
        void resetTransformacion();
    private:
        glm::mat4 transformacion;
        glm::vec3 traslacion;
        glm::vec3 ejeRotacion;
        GLfloat anguloRotacion = 0.0;
        glm::vec3 escalado;
    };
} // namespace PAG

#endif // TRANSFORMADOR_MODELO_H
