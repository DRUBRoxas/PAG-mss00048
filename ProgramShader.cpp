//
// Created by Manuel on 07/10/2024.
//

#include "ProgramShader.h"

#include <fstream>
#include <sstream>
#include <stdexcept>

namespace PAG {
    //Destructor
    ProgramShader::~ProgramShader() {
        if ( idSP != 0 )
        { glDeleteProgram ( idSP );
        }
        if ( idVS != 0 )
        { glDeleteShader ( idVS );
        }
        if ( idFS != 0 )
        { glDeleteShader ( idFS );
        }
    }

    ProgramShader::ProgramShader() {
    }
    void ProgramShader::enlazar() {
        //SHADER PROGRAM
        idSP = glCreateProgram ();
        glAttachShader ( idSP, idVS );
        glAttachShader ( idSP, idFS );
        glLinkProgram ( idSP );
        GLint resultadoEnlazado = 0;
        glGetProgramiv ( idSP, GL_LINK_STATUS, &resultadoEnlazado );
        if ( resultadoEnlazado == GL_FALSE )
        {  // Ha habido un error y hay que recuperar su descripción, para saber qué ha pasado
            GLint tamMsj = 0;
            std::string mensaje = "";
            glGetProgramiv ( idSP, GL_INFO_LOG_LENGTH, &tamMsj );
            if ( tamMsj > 0 )
            {  GLchar* mensajeFormatoC = new GLchar[tamMsj];
                GLint datosEscritos = 0;
                glGetProgramInfoLog ( idSP, tamMsj, &datosEscritos, mensajeFormatoC );
                mensaje.assign ( mensajeFormatoC );
                delete[] mensajeFormatoC;
                mensajeFormatoC = nullptr;
                throw std::runtime_error("Error al enlazar el shader program: "+mensaje);
            }
        }
    }

    std::pair<std::string, std::string> ProgramShader::CargaArchivos(std::string nombre) {
        nombreArchivo = nombre;
        std::ifstream archivoShader;
        std::pair<std::string, std::string> codigoFuente;
        std::string rutaFuenteGLSL = "shaders/" + nombre;
        std::string rutaFuenteFS = rutaFuenteGLSL + "-fs.glsl";
        std::string rutaFuenteVS = rutaFuenteGLSL + "-vs.glsl";

        // Leer el archivo del fragment shader
        archivoShader.open(rutaFuenteFS);
        if (!archivoShader.is_open()) {
            throw std::runtime_error("Error al abrir el archivo: " + rutaFuenteFS);
        }
        std::stringstream streamFS;
        streamFS << archivoShader.rdbuf();
        codigoFuente.second = streamFS.str();
        archivoShader.close();
        if (codigoFuente.second.empty()) {
            throw std::runtime_error("Error al leer el archivo: " + rutaFuenteFS);
        }

        // Leer el archivo del vertex shader
        archivoShader.open(rutaFuenteVS);
        if (!archivoShader.is_open()) {
            throw std::runtime_error("Error al abrir el archivo: " + rutaFuenteVS);
        }
        std::stringstream streamVS;
        streamVS << archivoShader.rdbuf();
        codigoFuente.first = streamVS.str();
        archivoShader.close();
        if (codigoFuente.first.empty()) {
            throw std::runtime_error("Error al leer el archivo: " + rutaFuenteVS);
        }

        return codigoFuente;
    }

    void ProgramShader::compilaShader(std::string nombreArchivo) {
        std::pair<std::string,std::string> codigoFuente = CargaArchivos(nombreArchivo);

        //Vertex Shader
        GLint resultadoCompilacion;
        idVS = glCreateShader ( GL_VERTEX_SHADER );
        const GLchar* fuenteVS = codigoFuente.first.c_str ();
        glShaderSource ( idVS, 1, &fuenteVS, nullptr );
        glCompileShader ( idVS );
        // Comprobamos si la compilación ha sido correcta
        glGetShaderiv ( idVS, GL_COMPILE_STATUS, &resultadoCompilacion );
        if(resultadoCompilacion == GL_FALSE)
        {
            GLint longitudMensaje;
            std::string mensaje="";
            glGetShaderiv ( idVS, GL_INFO_LOG_LENGTH, &longitudMensaje );
            if ( longitudMensaje > 0 )
            {
                GLchar* mensajeError = new GLchar[longitudMensaje];
                glGetShaderInfoLog ( idVS, longitudMensaje, nullptr, mensajeError );
                mensaje.assign(mensajeError);
                delete[] mensajeError;
                mensajeError = nullptr;
                throw std::runtime_error("Error al compilar el vertex shader: "+mensaje);
            }
        }

        //FRAGMENT SHADER
        idFS = glCreateShader ( GL_FRAGMENT_SHADER );
        const GLchar* fuenteFS = codigoFuente.second.c_str ();
        glShaderSource ( idFS, 1, &fuenteFS, nullptr );
        glCompileShader ( idFS );
        // Comprobamos si la compilación ha sido correcta
        glGetShaderiv ( idFS, GL_COMPILE_STATUS, &resultadoCompilacion );
        if(resultadoCompilacion == GL_FALSE)
        {
            GLint longitudMensaje;
            std::string mensaje="";
            glGetShaderiv ( idVS, GL_INFO_LOG_LENGTH, &longitudMensaje );
            if ( longitudMensaje > 0 )
            {
                GLchar* mensajeError = new GLchar[longitudMensaje];
                glGetShaderInfoLog ( idVS, longitudMensaje, nullptr, mensajeError );
                mensaje.assign(mensajeError);
                delete[] mensajeError;
                mensajeError = nullptr;
                throw std::runtime_error("Error al compilar el fragment shader: "+mensaje);
            }
        }
    }


} // PAG