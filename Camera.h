// Camera.h
#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/gl.h>
namespace PAG {

    class Camera {
    public:
        // Constructor
        Camera(glm::vec3 position, glm::vec3 lookAt, glm::vec3 up, float fovY, float aspect, float zNear, float zFar);

        Camera();

        void CalcularFovY();


        // Métodos para obtener las matrices de transformación
        glm::mat4 getViewMatrix() const;
        glm::mat4 getProjectionMatrix() const;
        void CalcularMVP();
        glm::mat4 getMVP() const;



        void cambiarAspecto(float ancho, GLfloat alto);

        // Movimientos de cámara
        void Pan(float angle);
        void Tilt(float angle);
        void Dolly(float movX, GLfloat movY);
        void Crane(float distance);
        void Orbit(float angleH, float angleV);

        void ResetCamera();

        void Zoom(GLfloat zoomAplicado);

        void setCamera(Camera *camara);

    private:
        glm::vec3 position, lookAt, up;
        GLfloat fovY,fovX, aspect, zNear, zFar;
        glm::mat4 viewMatrix, projectionMatrix;
        glm::mat4 matrizMVP;
        void updateViewMatrix();
        void updateProjectionMatrix();
    };

} // namespace PAG

#endif // CAMERA_H
