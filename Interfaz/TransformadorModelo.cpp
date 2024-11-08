#include "TransformadorModelo.h"

#include "Gui.h"


namespace PAG {
    TransformadorModelo::TransformadorModelo(){
    }
    TransformadorModelo::~TransformadorModelo(){
    }

    void TransformadorModelo::RefrescarTransformadorModelo() {
        int modeloSeleccionado=PAG::Gui::getInstancia().selectorModelo->getModeloSeleccionado();
        if(ImGui::Begin("Transformador de modelo")) {
            if (modeloSeleccionado<0) {
                ImGui::Text("No hay ningún modelo seleccionado");
            }else {
              // Control de traslación con etiquetas únicas y mejor organización
            ImGui::Text("Traslación");
            ImGui::Text("Eje X:");
            if (ImGui::Button("X+##TransX")) { traslacion.x += 10.0f; actualizarTransformacion(); }
            ImGui::SameLine();
            if (ImGui::Button("X-##TransX")) { traslacion.x -= 10.0f; actualizarTransformacion();}

            ImGui::Text("Eje Y:");
            if (ImGui::Button("Y+##TransY")) { traslacion.y += 10.0f; actualizarTransformacion();}
            ImGui::SameLine();
            if (ImGui::Button("Y-##TransY")) { traslacion.y -= 10.0f; actualizarTransformacion();}

            ImGui::Text("Eje Z:");
            if (ImGui::Button("Z+##TransZ")) { traslacion.z += 10.0f; actualizarTransformacion();}
            ImGui::SameLine();
            if (ImGui::Button("Z-##TransZ")) { traslacion.z -= 10.0f; actualizarTransformacion();}

            // Control de rotación con etiquetas únicas
            ImGui::Separator();
            ImGui::Text("Rotación");
            ImGui::Text("Eje X:");
            if (ImGui::Button("X+##RotX")) { rotacion.x += 10.0f; actualizarTransformacion();}
            ImGui::SameLine();
            if (ImGui::Button("X-##RotX")) { rotacion.x -= 10.0f; actualizarTransformacion();}

            ImGui::Text("Eje Y:");
            if (ImGui::Button("Y+##RotY")) { rotacion.y += 10.0f; actualizarTransformacion();}
            ImGui::SameLine();
            if (ImGui::Button("Y-##RotY")) { rotacion.y -= 10.0f; actualizarTransformacion();}

            ImGui::Text("Eje Z:");
            if (ImGui::Button("Z+##RotZ")) { rotacion.z += 10.0f; actualizarTransformacion();}
            ImGui::SameLine();
            if (ImGui::Button("Z-##RotZ")) { rotacion.z -= 10.0f; actualizarTransformacion();}

            // Control de escala con etiquetas únicas
            ImGui::Separator();
            ImGui::Text("Escala uniforme");
            if (ImGui::Button("Aumentar##Escala")) { escalado.x += 0.1f; actualizarTransformacion();}
            ImGui::SameLine();
            if (ImGui::Button("Disminuir##Escala")) { escalado.x = std::max(0.1f, escalado.x - 0.1f); actualizarTransformacion();}

            // Igualar escalas en los tres ejes
            escalado.y = escalado.x;
            escalado.z = escalado.x;

            // Botón para aplicar la transformación
            ImGui::Separator();
            if (ImGui::Button("Aplicar Transformación##Aplicar")) {
                transformacion = actualizarTransformacion();
            }
            }
        }ImGui::End();
    }

    glm::mat4 TransformadorModelo::actualizarTransformacion() {
        glm::mat4 transform = glm::mat4(1.0f);
        transform = glm::translate(transform, traslacion);

        transformacionAplicada = true;
        return transform;
    }

    glm::mat4 TransformadorModelo::getTransformacion() {
            transformacionAplicada = false;
            return transformacion;
    }




} // namespace PAG
