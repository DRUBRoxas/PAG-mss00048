//
// Created by Manuel on 07/10/2024.
//
#include <stdexcept>
#include <glad/glad.h>
#include "ProgramShader.h"

#include "Shader.h"


namespace PAG {
    //Destructor
    ProgramShader::~ProgramShader() {
        if (idSP != 0) {
            glDeleteProgram(idSP);
        }
        if (idVS != 0) {
            glDeleteShader(idVS);
        }
        if (idFS != 0) {
            glDeleteShader(idFS);
        }
    }

    ProgramShader::ProgramShader() {
    }

    void ProgramShader::enlazar() {
        //SHADER PROGRAM
        idSP = glCreateProgram();
        glAttachShader(idSP, idVS);
        glAttachShader(idSP, idFS);
        glLinkProgram(idSP);
        GLint resultadoEnlazado = 0;
        glGetProgramiv(idSP, GL_LINK_STATUS, &resultadoEnlazado);
        if (resultadoEnlazado == GL_FALSE) {
            // Ha habido un error y hay que recuperar su descripción, para saber qué ha pasado
            GLint tamMsj = 0;
            std::string mensaje = "";
            glGetProgramiv(idSP, GL_INFO_LOG_LENGTH, &tamMsj);
            if (tamMsj > 0) {
                GLchar *mensajeFormatoC = new GLchar[tamMsj];
                GLint datosEscritos = 0;
                glGetProgramInfoLog(idSP, tamMsj, &datosEscritos, mensajeFormatoC);
                mensaje.assign(mensajeFormatoC);
                delete[] mensajeFormatoC;
                mensajeFormatoC = nullptr;
                throw std::runtime_error("Error al enlazar el shader program: " + mensaje);
            }
        }
    }

    void ProgramShader::ObtenShaders(std::string nombre) {
        nombreArchivo = nombre;
        std::pair<std::string, std::string> codigoFuente;
        std::string rutaFuenteGLSL = "shaders/" + nombre;
        std::string rutaFuenteFS = rutaFuenteGLSL + "-fs.glsl";
        std::string rutaFuenteVS = rutaFuenteGLSL + "-vs.glsl";
        Shader *shaderVS = new Shader(rutaFuenteVS, GL_VERTEX_SHADER);
        Shader *shaderFS = new Shader(rutaFuenteFS, GL_FRAGMENT_SHADER);
        idVS = shaderVS->getIdShader();
        idFS = shaderFS->getIdShader();
        enlazar();
    }
} //PAG
