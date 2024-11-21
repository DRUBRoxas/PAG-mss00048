#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>
#include "TransformadorModelo.h"
#include "Gui.h"


namespace PAG {
    TransformadorModelo::TransformadorModelo(): transformacion(1.0), traslacion(0)
                                                , ejeRotacion(0, 1, 0), escalado(1) {
    }

    TransformadorModelo::~TransformadorModelo() {
    }

    void TransformadorModelo::RefrescarTransformadorModelo() {
        int modeloSeleccionado = PAG::Gui::getInstancia().selectorModelo->getModeloSeleccionado();
        if (ImGui::Begin("Transformador de modelo")) {
            if (modeloSeleccionado < 0) {
                ImGui::Text("No hay ningún modelo seleccionado");
            } else {
                // Control de traslación con etiquetas únicas y mejor organización
                ImGui::Text("Traslación");
                ImGui::Text("Eje X:");
                if (ImGui::Button("X+##TransX")) {
                    traslacion.x += 1.0f;
                }
                ImGui::SameLine();
                if (ImGui::Button("X-##TransX")) {
                    traslacion.x -= 1.0f;
                }

                ImGui::Text("Eje Y:");
                if (ImGui::Button("Y+##TransY")) {
                    traslacion.y += 1.0f;
                }
                ImGui::SameLine();
                if (ImGui::Button("Y-##TransY")) {
                    traslacion.y -= 1.0f;
                }

                ImGui::Text("Eje Z:");
                if (ImGui::Button("Z+##TransZ")) {
                    traslacion.z += 1.0f;
                }
                ImGui::SameLine();
                if (ImGui::Button("Z-##TransZ")) {
                    traslacion.z -= 1.0f;
                }

                // Control de rotación con etiquetas únicas
                static int ejeSeleccionado = 0;
                const char *opcionesEje[] = {"X", "Y", "Z"};

                //Selector de Eje
                ImGui::Separator();
                ImGui::Text("Rotación");
                ImGui::Text("Eje de rotación:");
                ImGui::SameLine();
                if(ImGui::BeginCombo("Eje##Rot", opcionesEje[ejeSeleccionado])) {
                    for (int i=0; i<3; i++) {
                        bool isSelected = (ejeSeleccionado == i);
                        if (ImGui::Selectable(opcionesEje[i], isSelected)) {
                            ejeSeleccionado = i;
                            ejeRotacion = glm::vec3(0.0f);
                            if (i==0) ejeRotacion.x = 1.0f;
                            if (i==1) ejeRotacion.y = 1.0f;
                            if (i==2) ejeRotacion.z = 1.0f;
                        }
                        if (isSelected) {
                            ImGui::SetItemDefaultFocus();
                        }
                    }
                    ImGui::EndCombo();
                }
                // Control del ángulo de rotación
                ImGui::Separator();
                ImGui::Text("Control del ángulo de rotación:");
                if (ImGui::Button("Incrementar##Angulo")) {
                    anguloRotacion += 0.1f; // Incrementar ángulo
                }
                ImGui::SameLine();
                if (ImGui::Button("Decrementar##Angulo")) {
                    anguloRotacion -= 0.1f; // Decrementar ángulo
                }

                // Control de escala con etiquetas únicas
                ImGui::Separator();
                ImGui::Text("Escala uniforme");
                if (ImGui::Button("Aumentar##Escala")) {
                    escalado.x += 0.1f;
                    escalado.y = escalado.x;
                    escalado.z = escalado.x;
                }
                ImGui::SameLine();
                if (ImGui::Button("Disminuir##Escala")) {
                    escalado.x = std::max(0.1f, escalado.x - 0.1f); // Igualar escalas en los tres ejes
                    escalado.y = escalado.x;
                    escalado.z = escalado.x;
                }
                // Botón para aplicar la transformación
                ImGui::Separator();
                if (ImGui::Button("Aplicar Transformación##Aplicar")) {
                    transformacion = actualizarTransformacion();
                }
            }
        }
        ImGui::End();
    }

    glm::mat4 TransformadorModelo::actualizarTransformacion() {
        // OJO: para componer las transformaciones, se multiplican las matrices de derecha a izquierda
        glm::mat4 t = glm::translate(traslacion);
        glm::mat4 r = glm::rotate(anguloRotacion, ejeRotacion);
        glm::mat4 s = glm::scale(escalado);

        transformacion = t * r * s;
        transformacionAplicada = true;
        return transformacion;
    }

    glm::mat4 TransformadorModelo::getTransformacion() {
        transformacionAplicada = false;
        return transformacion;
    }

    void TransformadorModelo::resetTransformacion() {
        transformacion = glm::mat4(1);
        traslacion = {0, 0, 0};
        ejeRotacion = {0, 0, 0};
        anguloRotacion = 0;
        escalado = {1, 1, 1};
    }
} // namespace PAG
