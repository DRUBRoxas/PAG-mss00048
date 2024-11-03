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
#include <glm/gtc/type_ptr.hpp>
#include <glm/fwd.hpp>
#include "../Modelado/Modelo.h"
#include <assimp/mesh.h>
#include <assimp/vector3.h>

#include "ProgramShader.h"
#include "../Camera.h"
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

        //Variables para almacenar el código fuente de los shaders
        std::string fuenteVS; // Código fuente del vertex shader
        std::string fuenteFS; // Código fuente del fragment shader


        PAG::ProgramShader *shaderProgram; // Shader program
        bool exito=false; // Para saber si se ha cargado correctamente el shader program
        static Renderer *instancia; ///< Instancia única de la clase
        Renderer();
        glm::mat4 viewMatrix, projectionMatrix;
        //guardamos las coordenadas RGBA del color de fondo
        float r = 0.6;
        float g = 0.6;
        float b = 0.6;
        float a=1.0;


    public:
        Camera camara; // Cámara de la escena
        Modelo *modelo;
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

        void setCamera(const Camera &camera);

        Camera getCamara();

        void creaModelo();
    };
} // PAG

#endif //RENDERER_H
