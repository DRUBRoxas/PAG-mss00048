#version 410

in vec4 colorDestino; // Color del modelo
out vec4 colorFragmento; // Color final del fragmento

// Declaración de subrutinas para calcular colores
subroutine vec4 calcularColor();
subroutine uniform calcularColor metodoColorElegido;



// Uniform para pasar un color desde el Renderer, contiene el color especular
uniform vec4 kD;

// Subrutina para el color rojo (modo alambre)
subroutine(calcularColor)
vec4 colorRojo() {
return vec4(1.0, 0.0, 0.0, 1.0);
}

// Subrutina para el color original (modo sólido)
subroutine(calcularColor)
vec4 colorOriginal() {
return colorDestino;
}

subroutine(calcularColor)
vec4 colorDifuso() {
return kD;
}

// Función principal del fragment shader
void main() {
colorFragmento = metodoColorElegido();
}