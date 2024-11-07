#include <iostream>
// IMPORTANTE: El include de GLAD debe estar siempre ANTES de el de GLFW
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>

#include "Camera.h"
#include "Interfaz/Gui.h"
#include "Renderizado/Renderer.h"
#include "Interfaz/imgui/imgui.h"
#include "Modelado/Modelo.h"

//Constantes
// Esta función callback será llamada cuando GLFW produzca algún error
void error_callback(int errno, const char *desc) {
    std::string aux(desc);
    PAG::Gui::getInstancia().consola->NuevoMensaje("Error de GLFW número " + std::to_string(errno) + ": " + aux);
}

// Esta función callback será llamada cada vez que el área de dibujo
// OpenGL deba ser redibujada.
void window_refresh_callback(GLFWwindow *window) {
    PAG::Renderer::getInstancia().refrescar();
    // GLFW usa un doble buffer para que no haya parpadeo. Esta orden
    // intercambia el buffer back (que se ha estado dibujando) por el
    // que se mostraba hasta ahora front. Debe ser la última orden de
    // este callback
    glfwSwapBuffers(window);
  //  PAG::Gui::getInstancia().consola->NuevoMensaje("Refresh callback called");
}

// Esta función callback será llamada cada vez que se cambie el tamaño
// del área de dibujo OpenGL.
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    PAG::Renderer::getInstancia().ResizeVentana(width, height);
    PAG::Renderer::getInstancia().camara.cambiarAspecto(width, height);
    //PAG::Gui::getInstancia().consola->NuevoMensaje("Resize callback called");
}

// Esta función callback será llamada cada vez que se pulse una tecla
// dirigida al área de dibujo OpenGL.
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }

    //Cargar modelos con las teclas del teclado
    if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
        PAG::Renderer::getInstancia().modelos.push_back(new PAG::Modelo("Modelos/Ajax.obj"));
        PAG::Renderer::getInstancia().creaModelos();
    }
    if (key == GLFW_KEY_2 && action == GLFW_PRESS) {
        PAG::Renderer::getInstancia().modelos.push_back(new PAG::Modelo("Modelos/dado.obj"));
        PAG::Renderer::getInstancia().creaModelos();
    }
    if (key == GLFW_KEY_3 && action == GLFW_PRESS) {
        PAG::Renderer::getInstancia().modelos.push_back(new PAG::Modelo("Modelos/mandalorian.obj"));
        PAG::Renderer::getInstancia().creaModelos();
    }
    if (key == GLFW_KEY_4 && action == GLFW_PRESS) {
        PAG::Renderer::getInstancia().modelos.push_back(new PAG::Modelo("Modelos/panther.obj"));
        PAG::Renderer::getInstancia().creaModelos();
    }
    if (key == GLFW_KEY_5 && action == GLFW_PRESS) {
        PAG::Renderer::getInstancia().modelos.push_back(new PAG::Modelo("Modelos/t-rex.obj"));
        PAG::Renderer::getInstancia().creaModelos();
    }
    if (key == GLFW_KEY_6 && action == GLFW_PRESS) {
        PAG::Renderer::getInstancia().modelos.push_back(new PAG::Modelo("Modelos/vaca.obj"));
        PAG::Renderer::getInstancia().creaModelos();
    }
    //Borrar modelos con las teclas del teclado
    if (key == GLFW_KEY_7 && action == GLFW_PRESS) {
        PAG::Renderer::getInstancia().borraModelo("Modelos/Ajax.obj");
    }
    if (key == GLFW_KEY_8 && action == GLFW_PRESS) {
        PAG::Renderer::getInstancia().borraModelo("Modelos/dado.obj");
    }
    if (key == GLFW_KEY_9 && action == GLFW_PRESS) {
        PAG::Renderer::getInstancia().borraModelo("Modelos/mandalorian,obj");
    }
    if (key == GLFW_KEY_0 && action == GLFW_PRESS) {
        PAG::Renderer::getInstancia().borraModelo("Modelos/panther.obj");
    }
    if (key == GLFW_KEY_MINUS && action == GLFW_PRESS) {
        PAG::Renderer::getInstancia().borraModelo("Modelos/t-rex.obj");
    }
    if (key == GLFW_KEY_EQUAL && action == GLFW_PRESS) {
        PAG::Renderer::getInstancia().borraModelo("Modelos/vaca.obj");
    }

    //Flechas para mover el modelo 0 (TODO: Cambiar al modelo seleccionado)
    if(key== GLFW_KEY_LEFT && action == GLFW_PRESS){
        PAG::Renderer::getInstancia().modelos[0]->setTransformacion(glm::translate(PAG::Renderer::getInstancia().modelos[0]->getTransformacion(),glm::vec3(-1.0f,0.0f,0.0f)));
    }
    if(key== GLFW_KEY_RIGHT && action == GLFW_PRESS){
        PAG::Renderer::getInstancia().modelos[0]->setTransformacion(glm::translate(PAG::Renderer::getInstancia().modelos[0]->getTransformacion(),glm::vec3(1.0f,0.0f,0.0f)));
    }
    if(key== GLFW_KEY_UP && action == GLFW_PRESS){
        PAG::Renderer::getInstancia().modelos[0]->setTransformacion(glm::translate(PAG::Renderer::getInstancia().modelos[0]->getTransformacion(),glm::vec3(0.0f,1.0f,0.0f)));
    }
    if(key== GLFW_KEY_DOWN && action == GLFW_PRESS){
        PAG::Renderer::getInstancia().modelos[0]->setTransformacion(glm::translate(PAG::Renderer::getInstancia().modelos[0]->getTransformacion(),glm::vec3(0.0f,-1.0f,0.0f)));
    }

    //Flechas para rotar el modelo 0 (TODO: Cambiar al modelo seleccionado)
    //TODO: Comprobar rotacion con Fran o con Angel Luis, esto creo que está mal
    if(key== GLFW_KEY_K && action == GLFW_PRESS){
        PAG::Renderer::getInstancia().modelos[0]->setTransformacion(glm::rotate(PAG::Renderer::getInstancia().modelos[0]->getTransformacion(),glm::radians(10.0f),glm::vec3(0.0f,0.0f,1.0f)));
    }
    if(key== GLFW_KEY_L && action == GLFW_PRESS){
        PAG::Renderer::getInstancia().modelos[0]->setTransformacion(glm::rotate(PAG::Renderer::getInstancia().modelos[0]->getTransformacion(),glm::radians(-10.0f),glm::vec3(0.0f,0.0f,1.0f)));
    }
    if(key== GLFW_KEY_I && action == GLFW_PRESS){
        PAG::Renderer::getInstancia().modelos[0]->setTransformacion(glm::rotate(PAG::Renderer::getInstancia().modelos[0]->getTransformacion(),glm::radians(10.0f),glm::vec3(1.0f,0.0f,0.0f)));
    }
    if(key== GLFW_KEY_O && action == GLFW_PRESS){
        PAG::Renderer::getInstancia().modelos[0]->setTransformacion(glm::rotate(PAG::Renderer::getInstancia().modelos[0]->getTransformacion(),glm::radians(-10.0f),glm::vec3(1.0f,0.0f,0.0f)));
    }

    //Flechas para escalar el modelo 0 (TODO: Cambiar al modelo seleccionado)
    if(key== GLFW_KEY_N && action == GLFW_PRESS){
        PAG::Renderer::getInstancia().modelos[0]->setTransformacion(glm::scale(PAG::Renderer::getInstancia().modelos[0]->getTransformacion(),glm::vec3(1.1f,1.1f,1.1f)));
    }
    if(key== GLFW_KEY_M && action == GLFW_PRESS){
        PAG::Renderer::getInstancia().modelos[0]->setTransformacion(glm::scale(PAG::Renderer::getInstancia().modelos[0]->getTransformacion(),glm::vec3(0.9f,0.9f,0.9f)));
    }
}

// Esta función callback será llamada cada vez que se pulse algún botón
// del ratón sobre el área de dibujo OpenGL.
void mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
    ///Cambiar el color del fondo al mover la rueda del ratón

}

// Esta función callback será llamada cada vez que se mueva la rueda
// del ratón sobre el área de dibujo OpenGL.
//DEPRECATED
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    // std::cout << "Movida la rueda del raton " << xoffset
    //         << " Unidades en horizontal y " << yoffset
    //         << " unidades en vertical" << std::endl;

    const int r = 0 + rand() % 10;
    const int g = 0 + rand() % 10;
    const int b = 0 + rand() % 10;
    PAG::Renderer::getInstancia().CambiarColorFondo(r / 10.0, g / 10.0, b / 10.0, 1.0);
    PAG::Gui::getInstancia().consola->NuevoMensaje("Movida la rueda del raton. Cambiando color de fondo a" + std::to_string(r) + " " + std::to_string(g) + " " + std::to_string(b));
}

int main() {

    /*
     *TODO:
     * Cambiar el uso de los movimientos de la cámara fuera de la interfaz
     * Crear un sistema de carga de modelos
     *
     */
    PAG::Gui::getInstancia().asignarCamara(&PAG::Renderer::getInstancia().camara);
    PAG::Gui::getInstancia().consola->NuevoMensaje("Starting Application PAG-Prueba 01");
    //-Este callback hay que registrarlo ANTES de llamar a glfwInit
    glfwSetErrorCallback((GLFWerrorfun) error_callback);
    // Inicializa GLFW. Es un proceso que sólo debe realizarse una vez en la aplicación
    if (glfwInit() != GLFW_TRUE) {
        PAG::Gui::getInstancia().consola->NuevoMensaje("Failed to initialize GLFW");
        return -1;
    }
    // Definimos las características que queremos que tenga el contexto gráfico
    // OpenGL de la ventana que vamos a crear. Por ejemplo, el número de muestras o el
    // modo Core Profile.
    glfwWindowHint(GLFW_SAMPLES, 4); // Activa antialiasing con 4 muestras.
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Esta y las 2
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // siguientes activan un contexto
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1); // OpenGL Core Profile 4.1.
    // Definimos el puntero para guardar la dirección de la ventana de la aplicación y
    // la creamos
    GLFWwindow *window;
    // Tamaño, título de la ventana, en ventana y no en pantalla completa,
    // sin compartir recursos con otras ventanas.
    window = glfwCreateWindow(1600,1400, "PAG Introduction", nullptr, nullptr);
    // Comprobamos si la creación de la ventana ha tenido éxito.
    if (window == nullptr) {
        PAG::Gui::getInstancia().consola->NuevoMensaje("Failed to open GLFW window");
        glfwTerminate(); // Liberamos los recursos que ocupaba GLFW.
        return -2;
    }
    // Hace que el contexto OpenGL asociado a la ventana que acabamos de crear pase a
    // ser el contexto actual de OpenGL para las siguientes llamadas a la biblioteca
    glfwMakeContextCurrent(window);
    // Ahora inicializamos GLAD.
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        PAG::Gui::getInstancia().consola->NuevoMensaje("GLAD initialization failed");
        glfwDestroyWindow(window); // Liberamos los recursos que ocupaba GLFW.
        window = nullptr;
        glfwTerminate();
        return -3;
    }
    // Contexto de la App (para checkar que vaya gucci)
    PAG::Gui::getInstancia().consola->NuevoMensaje(PAG::Renderer::getInstancia().ObtenerDatos());

    // Registramos los callbacks que responderán a los eventos principales
    glfwSetWindowRefreshCallback(window, window_refresh_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // Inicializamos OpenGL,imgui y cargamos los shaders
    PAG::Renderer::getInstancia().inicializaOpenGL();
    PAG::Gui::getInstancia().StartGui(window);
    // Ciclo de eventos de la aplicación.
    while (!glfwWindowShouldClose(window)) {
        // Borra los buffers (color y profundidad)
        PAG::Renderer::getInstancia().refrescar();
        PAG::Gui::getInstancia().RefrescarFrame();
        // Hace el SWAP del doble buffer
        glfwSwapBuffers(window);

        // Obtiene y organiza los eventos pendientes, tales como pulsaciones de
        // teclas o de ratón, etc. Siempre al final de cada iteración del ciclo
        // de eventos y después de glfwSwapBuffers(window);
        glfwPollEvents();
    }
    // Liberamos recursos
    PAG::Gui::getInstancia().EndGui();
    PAG::Gui::getInstancia().consola->NuevoMensaje("Finishing application pag prueba");
    glfwDestroyWindow(window); // Cerramos y destruimos la ventana de la aplicación.
    window = nullptr;
    glfwTerminate(); // Liberamos los recursos que ocupaba GLFW.
}
