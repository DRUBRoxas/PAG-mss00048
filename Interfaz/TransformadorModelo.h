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
        glm::mat4 transformacion=glm::mat4(0.0);
        glm::vec3 traslacion=glm::vec3(0.0);
        glm::vec3 ejeRotacion=glm::vec3(0.0);
        GLfloat anguloRotacion = 0.0;
        glm::vec3 escalado=glm::vec3(1.0);
    };
} // namespace PAG

#endif // TRANSFORMADOR_MODELO_H
