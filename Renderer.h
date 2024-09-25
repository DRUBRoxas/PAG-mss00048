//
// Created by Manuel on 20/09/2024.
//

#ifndef RENDERER_H
#define RENDERER_H
#include <string>
#include <glad/glad.h>
/**
 * Espacio de nombres para las prácticas de Programación de Aplicaciones
 * Gráficas
 */
namespace PAG {
    /**
     * @brief Clase encargada de encapsular la gestión del área de dibujo
     * OpenGL
     *
     * Esta clase coordina el renderizado de las escenas OpenGL. Se implementa
     * aplicando el patrón de diseño Singleton. Está pensada para que las
     * funciones callback hagan llamadas a sus métodos
     */
    class Renderer {
    private:
        static Renderer *instancia; ///< Instancia única de la clase
        Renderer();
        float r = 0.6;
        float g = 0.6;
        float b = 0.6;
        float a=1.0;

    public:
        virtual ~Renderer();
        static Renderer &getInstancia();
        void refrescar();
        void ResizeVentana(int ancho, int alto);

        std::string CambiarColorFondo(double r, double g, double b, double a);

        std::string ObtenerDatos();
        void ActivarProfundidad();
        void DesactivarProfundidad();
    };
} // PAG

#endif //RENDERER_H
