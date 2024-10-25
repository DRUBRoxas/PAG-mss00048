#version 410
layout (location = 0) in vec3 posicion;
layout (location = 1) in vec3 vColor;

out vec4 colorDestino;
uniform mat4 matrizMVP;
void main ()
{
    colorDestino = vec4(vColor,1.0);
    gl_Position = matrizMVP*vec4(posicion,1);
};