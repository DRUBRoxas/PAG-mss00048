#ifndef LUZ_H
#define LUZ_H

#include <glad/glad.h>
#include <glm/glm.hpp>
namespace PAG {
    enum class TipoLuz {
        AMBIENTE,
        PUNTUAL,
        DIRECCIONAL,
        FOCO
    };

    class Luz {
    private:
        TipoLuz tipo;
        glm::vec3 colorAmbiente=glm::vec3(0.0f);
        glm::vec3 colorDifuso=glm::vec3(0.0f);
        glm::vec3 colorEspecular=glm::vec3(0.0f);
        glm::vec3 posicion=glm::vec3(0.0f);
        glm::vec3 direccion=glm::vec3(0.0f);
        GLfloat gamma=0.0f;
        GLfloat exponente=0.0f;

    public:
        // Constructores
        Luz(TipoLuz tipo);
        Luz();

        // Destructor
        ~Luz() = default;

        //Métodos Inicializar
        void inicializarAmbiente(const glm::vec3& colorAmbiente);
        void inicializarPuntual(const glm::vec3& colorDifuso, const glm::vec3& colorEspecular, const glm::vec3& pos);
        void inicializarDireccional(const glm::vec3& direccion, const glm::vec3& colorDifuso, const glm::vec3& colorEspecular);
        void inicializarFoco(const glm::vec3& posicion,const glm::vec3& direccion, const glm::vec3& colorDifuso, const glm::vec3& colorEspecular,
            const GLfloat& gamma, const GLfloat& exponente);


        // Setters
        void setPosicion(const glm::vec3& pos);
        void setDireccion(const glm::vec3& dir);
        void setGamma(GLfloat angulo);
        void setExponente(GLfloat exp);

        // Getters
        TipoLuz getTipo() const;
        const glm::vec3& getColorAmbiente() const;
        const glm::vec3& getColorDifuso() const;
        const glm::vec3& getColorEspecular() const;
        const glm::vec3& getPosicion() const;
        const glm::vec3& getDireccion() const;
        GLfloat getGamma() const;
        GLfloat getExponente() const;
    };
}
#endif
