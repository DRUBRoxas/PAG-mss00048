#version 410
layout (location = 0) in vec3 posicion;
layout (location = 1) in vec4 vNormal;


uniform mat4 matrizMVP;
uniform mat4 matrizTransformacion;
uniform mat4 mModelView;

out vec3 position;
out vec3 normal;

void main()
{
    normal = vec3(mModelView*vNormal);
    position = vec3(mModelView*vec4(posicion, 1));
    gl_Position = matrizMVP*vec4(posicion, 1);

}