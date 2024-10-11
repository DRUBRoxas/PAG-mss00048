//
// Created by Manuel on 20/09/2024.
//

#ifndef RENDERER_H
#define RENDERER_H
#include <string>
#include <glad/glad.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

#include "ProgramShader.h"
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
        GLuint idVAO = 0; // Identificador del vertex array object
        GLuint idVBO = 0; // Identificador del vertex buffer object
        GLuint idIBO = 0; // Identificador del index buffer object

        //Variables para almacenar el código fuente de los shaders
        std::string fuenteVS; // Código fuente del vertex shader
        std::string fuenteFS; // Código fuente del fragment shader

        PAG::ProgramShader *shaderProgram; // Shader program
        bool exito=false; // Para saber si se ha cargado correctamente el shader program
        static Renderer *instancia; ///< Instancia única de la clase

        Renderer();
        //guardamos las coordenadas RGBA del color de fondo
        float r = 0.6;
        float g = 0.6;
        float b = 0.6;
        float a=1.0;

    public:
        virtual ~Renderer();
        static Renderer &getInstancia();
        void refrescar();
        void ResizeVentana(int ancho, int alto);

        void CambiarColorFondo(double r, double g, double b, double a);

        std::string ObtenerDatos();
        void ActivarProfundidad();
        void DesactivarProfundidad();

        void inicializaOpenGL();
        void creaModeloEntrelazado();

        void enlazarShaderProgram(std::string nombreArchivo);
    };
} // PAG

#endif //RENDERER_H
