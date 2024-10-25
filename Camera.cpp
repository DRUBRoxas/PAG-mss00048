// Camera.cpp
#include "Camera.h"

namespace PAG {
    Camera::Camera() {
        position = {0.0f, 0.0f, 5.0f};
        lookAt = {0.0f, 0.0f, 0.0f};
        up = {0.0f, 1.0f, 0.0f};
        fovX = 45.0f;
        aspect = 1600 / 1400;
        zNear = 0.1f;
        zFar = 100.0f;
        CalcularFovY();
        CalcularMVP();
    }

    void Camera::CalcularFovY() {
        //Asumo que el FovX esta en radianes
        fovY = 2 * glm::atan(glm::tan(glm::radians(fovX) / 2) / aspect);
    }

    // Obtener la matriz de vista
    glm::mat4 Camera::getViewMatrix() const {
        return glm::lookAt(position, lookAt, up);
    }

    // Obtener la matriz de proyección
    glm::mat4 Camera::getProjectionMatrix() const {
        return glm::perspective(fovY, aspect, zNear, zFar);
    }

    void Camera::CalcularMVP() {
        matrizMVP = getProjectionMatrix() * getViewMatrix();
    }

    void Camera::cambiarAspecto(GLfloat ancho, GLfloat alto) {
        aspect = ancho / alto;
        CalcularFovY();
        CalcularMVP();
    }

    // Actualiza la matriz de vista
    void Camera::updateViewMatrix() {
        viewMatrix = glm::lookAt(position, lookAt, up);
    }

    // Actualiza la matriz de proyección
    void Camera::updateProjectionMatrix() {
        projectionMatrix = glm::perspective(glm::radians(fovY), aspect, zNear, zFar);
    }

    glm::mat4 Camera::getMVP() const {
        return matrizMVP;
    }


    //MOVIMIENTOS CAMARA

    void Camera::Zoom(GLfloat zoomAplicado) {
        fovX += zoomAplicado;
        CalcularFovY();
        CalcularMVP();
    }

    void Camera::Crane(GLfloat distance) {
        glm::vec3 upVector = glm::normalize(up);
        position += upVector * distance;
        lookAt += upVector * distance;
        CalcularMVP();
    }

    void Camera::Tilt(GLfloat angle) {
        glm::vec3 right = glm::normalize(glm::cross(lookAt - position, up));
        glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(angle), right);
        glm::vec3 direction = glm::normalize(lookAt - position);
        direction = glm::vec3(rotation * glm::vec4(direction, 0.0f));
        lookAt = position + direction;
        up = glm::vec3(rotation * glm::vec4(up, 0.0f));
        CalcularMVP();
    }

    void Camera::Dolly(GLfloat movX, GLfloat movY) {
        // Calcular la dirección frontal (hacia donde mira la cámara)
        glm::vec3 forward = glm::normalize(lookAt - position);

        // Calcular el vector "right" (hacia los lados) como el producto cruzado entre forward y up
        glm::vec3 right = glm::normalize(glm::cross(forward, up));

        // Mover la cámara hacia adelante/atrás (eje Z local)
        position += forward * movY;
        lookAt += forward * movY;

        // Mover la cámara lateralmente (eje X local)
        position += right * movX;
        lookAt += right * movX;

        // Recalcular la matriz MVP
        CalcularMVP();
    }

    void Camera::Pan(float angle) {
        glm::vec3 right = glm::normalize(glm::cross(lookAt - position, up));
        position += right * angle;
        lookAt += right * angle;
        CalcularMVP();
    }

    void Camera::Orbit(float angleH, float angleV) {
        // Limitar el ángulo vertical (pitch) entre -89 y 89 grados
        angleV = glm::clamp(angleV, -89.0f, 89.0f);

        glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(angleH), up);
        rotation = glm::rotate(rotation, glm::radians(angleV), glm::normalize(glm::cross(lookAt - position, up)));

        glm::vec3 offset = lookAt - position;
        offset = glm::vec3(rotation * glm::vec4(offset, 1.0));

        // Asegurarse de que la nueva posición no coincida con lookAt
        if (glm::length(offset) > 0.1f) { // Puedes ajustar el umbral
            position = lookAt - offset;
        } else {
            position = lookAt - glm::normalize(offset) * 0.1f; // Ajuste por si está muy cerca
        }

        CalcularMVP();
    }

    void Camera::ResetCamera() {
        position = {0.0f, 0.0f, 5.0f};
        lookAt = {0.0f, 0.0f, 0.0f};
        up = {0.0f, 1.0f, 0.0f};
        fovX = 45.0f;
        aspect = 1600 / 1400;
        zNear = 0.1f;
        zFar = 100.0f;
        CalcularFovY();
        CalcularMVP();
    }








} // namespace PAG
