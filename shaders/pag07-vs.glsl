#version 410
layout (location = 0) in vec3 posicion;
layout (location = 1) in vec4 vColor;
uniform mat4 matrizMVP;
uniform mat4 matrizTransformacion;
out vec4 colorDestino;

void main()
{
    colorDestino = vColor;
    gl_Position = matrizMVP*vec4(posicion, 1);
}