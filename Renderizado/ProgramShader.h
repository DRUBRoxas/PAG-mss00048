//
// Created by Manuel on 07/10/2024.
//

#ifndef PROGRAMSHADER_H
#define PROGRAMSHADER_H
#include <string>
#include <utility>
#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "Shader.h"
namespace PAG {

class ProgramShader {
private:
    GLuint idSP = 0; // Identificador del shader program
    std::string nombreArchivo;
    //Identificadores shaders
    GLuint idVS = 0; // Identificador del vertex shader
    GLuint idFS = 0; // Identificador del fragment shader

    //Variables para almacenar el código fuente de los shaders
    std::string fuenteVS; // Código fuente del vertex shader
    std::string fuenteFS; // Código fuente del fragment shader
public:
    ProgramShader();
    virtual ~ProgramShader();
    void enlazar();

    void ObtenShaders(std::string nombre);

    GLuint getIdSP() const { return idSP; }
    void compilaShader(std::string nombreArchivo);

    std::string CargaArchivos(std::string nombreArchivo);
    GLuint getIdVS() const { return idVS; }
    GLuint getIdFS() const { return idFS; }
    std::string getNombreArchivo() const { return nombreArchivo; }
    std::string getFuenteVS() const { return fuenteVS; }
    std::string getFuenteFS() const { return fuenteFS; }
};

} // PAG

#endif //PROGRAMSHADER_H
