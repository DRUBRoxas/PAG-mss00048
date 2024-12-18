#version 410

in vec3 normal; // Normal del fragmento
in vec3 position; // Posición del fragmento
out vec4 colorFragmento; // Color final del fragmento

uniform vec3 Ka;
uniform vec3 Kd;
uniform vec3 Ks;

uniform vec3 Ia;
uniform vec3 Id;
uniform vec3 Is;
uniform float shininess;
uniform vec3 lightPosition;
uniform vec3 lightDirection;
uniform float spotAngle;

// Declaración de subrutinas
subroutine vec3 calcularLuces();
subroutine uniform calcularLuces metodoLucesElegido;

// Subrutina para calcular la luz ambiente
subroutine (calcularLuces)
    vec3 ambiente() {
        return (Ia * Ka);
    }

// Subrutina para calcular la luz puntual
subroutine (calcularLuces)
    vec3 puntual() {
        vec3 n = normalize(normal);
        vec3 l = normalize(lightPosition - position);
        vec3 v = normalize(-position);
        vec3 r = reflect(-l, n);
        vec3 especular;
        vec3 difusa = (Id * Kd * max(dot(l, n), 0.0));
        especular = (Is * Ks * pow(max(dot(r, v), 0.0), 2.0));
        return difusa + especular;
    }

// Subrutina para calcular la luz direccional
subroutine (calcularLuces)
    vec3 direccional() {
        vec3 n = normalize(normal);
        vec3 l = - lightDirection;
        vec3 v = normalize(-position);
        vec3 r = reflect(- l, n);

        vec3 difusa = Id * Kd* max(dot(l,n),0);
        vec3 especular;

        especular = (Is* Ks * pow(max(dot(r, v), 0), shininess));

        return difusa + especular;
    }
// Subrutina para calcular la luz spot
subroutine (calcularLuces)
    vec3 foco() {
        vec3 l = normalize(lightPosition - position);
        vec3 d = lightDirection;
        float cosGamma = cos(spotAngle * 180.0 / 3.14159265);
        float spotFactor = 1.0;

        if (dot(-l, d) < cosGamma){
        spotFactor = 0.0;
        }

        vec3 n = normalize(normal);
        vec3 v= normalize(- position);
        vec3 r = reflect(- l, n);

        vec3 difusa= Id * Kd * max(dot(l,n), 0);
        vec3 especular = Is * Ks * pow(max(dot(r, v), 0), shininess);

        return (difusa + especular) * spotFactor;
    }

// Subrutina en caso de que no haya luces
subroutine (calcularLuces)
    vec3 sinLuces() {
        return vec3(0.0, 1.0, 0.0);
    }
// Función principal del fragment shader
void main() {
colorFragmento = vec4(metodoLucesElegido(), 1.0);
}