//
// Created by Manuel on 11/10/2024.
//

#ifndef SHADER_H
#define SHADER_H
#include "../Renderizado/ProgramShader.h"

namespace PAG {

    class Shader {
    private:
        GLuint idShader;
        GLenum tipoShader;
    public:
        Shader(std::string ruta, GLenum tipo);
        ~Shader();
        std::string CargaArchivos(std::string ruta);
        Shader();
        void compilaShader(std::string ruta);
        GLuint getIdShader() const { return idShader; }
    };

} // PAG

#endif //SHADER_H
