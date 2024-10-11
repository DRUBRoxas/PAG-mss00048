# PAG-mss00048

# Autor:
- [Manuel Sánchez Salazar](mailto:mss00048@red.ujaen.es)
- [Perfil GitHub](https://github.com/DRUBRoxas/PAG-mss00048)

# Descripción:
Este repositorio contiene la práctica de la asignatura Programacion de Aplicaciones Gráficas.

# Practica 1:
## Ejercicio 1
Se ha realizado una función que permite que, al mover la rueda del ratón se genere un color aleatorio y se cambie el color de fonde del programa
## Ejercicio 2
Utilizar un Singleton puede ser una buena solución para este caso, ya que garantiza que haya una única instancia
de la clase PAG::Renderer en toda la aplicación y facilita el acceso global a esa instancia desde cualquier parte, 
incluyendo funciones de C registradas como callbacks.
Para implementar un singleton, necesitas:
* La clase tenga un único punto de acceso.
* El constructor sea privado, para que no se puedan crear más instancias.
* Se proporcione un método estático para obtener la instancia única.


![UMLSingleton.png](Assets/UMLSingleton.png)

Esto puede presentar las siguientes ventajas:
* Simplicidad en el código.
* Acceso global controlado.
* Encapsulamiento.


# Practica 2:
## Ejercicio 1
La clase PAG::Renderer ha sido completada, se han añadido los siguientes cambios:

![UMLRenderer.png](Assets%2FUMLRenderer.png)

## Ejercicio 2
Se han sustituido todas las llamadas a openGL en el main por llamadas a PAG::Renderer
## Ejercicio 3
Todos los mensajes han sido añadidos a la consola de Dear imgui y para el selector de color
se ha elegido un ColorPicker4, había varias opciones a elegir, y otras versiones de este mismo,
he usado esta porque me parece la mas sencilla y la que mejor se adapta a lo que necesitamos.
Para usarla se ha utilizado la flag:
```cpp
ImGuiColorEditFlags_PickerHueWheel
```
Hay muchas mas flags que permiten la modificación al gusto del selector del color, pero he decidido
usar solo esta por ahora.

# Practica 3:
## Ejercicio 5
Este comportamiento se debe a que la proyección y las coordenadas de la ventana no se están
ajustando correctamente cuando se redimensiona la ventana. Al cambiar el tamaño de la ventana,
la relación de aspecto de la ventana cambia, lo que significa que la proyección debee ajustarse a la nueva relación
de aspecto.

# Practica 4:
## Ejercicio 4
He creado la funcion auxiliar leerArchivo, que se encarga de leer los archivos, manejar los errores y leer el contenido
Se ha añadido y modificado el metodo cargaArchivos, para cargar las dos versiones del archivo glsl de golpe.
Se ha añadido manejo de excepciones en el metodo cargaArchivos, para asegurarse de que cuando se lance la excepcio, el mensaje se mande a la consola
y siga funcionando el programa. A parte de esto, se ha encapsulado en su propia clase el Shader Program, para que el renderer haga unicamente su trabajo.
Despues, desde la clase TextBox, se llama (con el nombre del archivo) al program shader, que se encarga de hacer todo lo demás.
![UMLPractica4.png](Assets%2FUMLPractica4.png)


# Practica 5
Cambios a la practica anterior, se ha desacoplado el shader y el shader program, separandolos cada uno en su propia clase y llevandolo mejor, el UML despues del cambio es:
> TODO: Añadir UML