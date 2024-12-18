#include "Luz.h"

#include <glad/glad.h>

namespace PAG {
    Luz::Luz(TipoLuz tipo) : tipo(tipo) {}

    Luz::Luz() {}

    // Métodos Inicializar
    void Luz::inicializarAmbiente(const glm::vec3& colorAmbiente) {
        this->colorAmbiente = colorAmbiente;
    }

    void Luz::inicializarPuntual(const glm::vec3 &colorDifuso, const glm::vec3 &colorEspecular, const glm::vec3 &pos) {
        this->colorDifuso=colorDifuso;
        this->colorEspecular=colorEspecular;
        this->posicion=pos;
    }


    void Luz::inicializarDireccional(const glm::vec3 &direccion, const glm::vec3 &colorDifuso, const glm::vec3 &colorEspecular) {
        this->direccion = direccion;
        this->colorDifuso = colorDifuso;
        this->colorEspecular = colorEspecular;
    }

    void Luz::inicializarFoco(const glm::vec3 &posicion, const glm::vec3 &direccion, const glm::vec3 &colorDifuso, const glm::vec3 &colorEspecular, const GLfloat &gamma, const GLfloat &exponente) {
        this->posicion = posicion;
        this->direccion = direccion;
        this->colorDifuso = colorDifuso;
        this->colorEspecular = colorEspecular;
        this->gamma = gamma;
        this->exponente = exponente;
    }

    // Getters y Setters
    void Luz::setPosicion(const glm::vec3& pos) { posicion = pos; }
    void Luz::setDireccion(const glm::vec3& dir) { direccion = dir; }
    void Luz::setGamma(GLfloat angulo) { gamma = angulo; }
    void Luz::setExponente(GLfloat exp) { exponente = exp; }

    TipoLuz Luz::getTipo() const { return tipo; }
    const glm::vec3& Luz::getColorAmbiente() const { return colorAmbiente; }
    const glm::vec3& Luz::getColorDifuso() const { return colorDifuso; }
    const glm::vec3& Luz::getColorEspecular() const { return colorEspecular; }
    const glm::vec3& Luz::getPosicion() const { return posicion; }
    const glm::vec3& Luz::getDireccion() const { return direccion; }
    GLfloat Luz::getGamma() const { return gamma; }
    GLfloat Luz::getExponente() const { return exponente; }
}
