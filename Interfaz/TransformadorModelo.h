#ifndef TRANSFORMADOR_MODELO_H
#define TRANSFORMADOR_MODELO_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace PAG {

    class TransformadorModelo {
    public:
        bool transformacionAplicada = false;
        TransformadorModelo();
        ~TransformadorModelo();

        glm::mat4 actualizarTransformacion();
        void RefrescarTransformadorModelo();
        glm::mat4 getTransformacion();
    private:
        glm::mat4 transformacion;
        glm::vec3 traslacion;
        glm::vec3 rotacion;
        glm::vec3 escalado;
    };
} // namespace PAG

#endif // TRANSFORMADOR_MODELO_H
