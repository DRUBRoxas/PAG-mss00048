//
// Created by Manuel on 11/10/2024.
//
#include <glad/glad.h>


#include "Shader.h"
#include <fstream>
#include <sstream>

namespace PAG {
    Shader::Shader(std::string ruta,GLenum tipo) {
        idShader = 0;
        tipoShader = tipo;
        compilaShader(ruta);
    }

    Shader::~Shader() {
        if(idShader != 0 ) {
            glDeleteShader(idShader);
        }
    }


    std::string Shader::CargaArchivos(std::string ruta) {
        // Leer el archivo del Shader
        std::string codigoFuente="";
        std::ifstream archivoShader;
        archivoShader.open(ruta);
        if (!archivoShader.is_open()) {
            throw std::runtime_error("Error al abrir el archivo: " + ruta);
        }
        std::stringstream streamFS;
        streamFS << archivoShader.rdbuf();
        codigoFuente = streamFS.str();
        archivoShader.close();
        if (codigoFuente.empty()) {
            throw std::runtime_error("Error al leer el archivo: " + ruta);
        }
        return codigoFuente;
    }

    void Shader::compilaShader(std::string ruta) {
        std::string codigoFuente = CargaArchivos(ruta);
        //Vertex Shader
        GLint resultadoCompilacion;
        idShader = glCreateShader(tipoShader);
        const GLchar *fuente = codigoFuente.c_str();
        glShaderSource(idShader, 1, &fuente, nullptr);
        glCompileShader(idShader);
        // Comprobamos si la compilación ha sido correcta
        glGetShaderiv(idShader, GL_COMPILE_STATUS, &resultadoCompilacion);
        if (resultadoCompilacion == GL_FALSE) {
            GLint longitudMensaje;
            std::string mensaje = "";
            glGetShaderiv(idShader, GL_INFO_LOG_LENGTH, &longitudMensaje);
            if (longitudMensaje > 0) {
                GLchar *mensajeError = new GLchar[longitudMensaje];
                glGetShaderInfoLog(idShader, longitudMensaje, nullptr, mensajeError);
                mensaje.assign(mensajeError);
                delete[] mensajeError;
                mensajeError = nullptr;
                throw std::runtime_error("Error al compilar el vertex shader: " + mensaje);
            }
        }
    }
} // PAG
