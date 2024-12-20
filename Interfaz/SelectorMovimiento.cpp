//
// Created by Manuel on 22/10/2024.
//

#include "SelectorMovimiento.h"

#include <glm/ext/quaternion_geometric.hpp>


#define _CRANE_SENSITIVITY_ 0.25f
#define _TILT_PAN_SENSITIVITY_ 0.25f
#define _DOLLY_SENSITIVITY_ 0.25f
#define _ORBIT_SENSITIVITY_ 9.0f
#define _ZOOM_SENSITIVITY_ 1.0f

namespace PAG {
    SelectorMovimiento::SelectorMovimiento() {
    }
    void SelectorMovimiento::RefrescarSelector() {
        const char* items[]={"Zoom","Crane","Tilt","Dolly","Pan","Orbit","Reset"};
        static const char* current_item = NULL;

        if(ImGui::Begin("Control Camara")) {
            ImGui::Text("Elige una opción:");

            if(ImGui::BeginCombo("##combo", current_item)) {
                for(int n=0; n<7; n++) {
                    bool is_selected = (current_item == items[n]);
                    if(ImGui::Selectable(items[n], is_selected)) {
                        current_item = items[n];
                    }
                    if(is_selected) {
                        ImGui::SetItemDefaultFocus();
                    }
                }
                ImGui::EndCombo();
            }
            //Change content based on option selected
            if(current_item=="Zoom"){
                if(ImGui::Button("Zoom In")){
                    camera->Zoom(_ZOOM_SENSITIVITY_*-1);
                }
                ImGui::SameLine();
                if(ImGui::Button("Zoom Out")){
                    camera->Zoom(_ZOOM_SENSITIVITY_);
                }
            }

            if(current_item=="Crane"){
                //Botón de Subir y de Bajar
                if(ImGui::Button("Subir")){
                    camera->Crane(_CRANE_SENSITIVITY_);
                }
                ImGui::SameLine();
                if(ImGui::Button("Bajar")){
                    camera->Crane(_CRANE_SENSITIVITY_ * -1);
                }
            }

            if(current_item=="Tilt"){
                if(ImGui::Button("Subir")){
                    camera->Tilt(_TILT_PAN_SENSITIVITY_);
                }
                ImGui::SameLine();
                if(ImGui::Button("Bajar")){
                    camera->Tilt(_TILT_PAN_SENSITIVITY_ * -1);
                }
            }
            if (current_item == "Dolly") {
                // Botón para mover hacia adelante (Dolly in)
                if (ImGui::Button("Adelante")) {
                    camera->Dolly(0, _DOLLY_SENSITIVITY_); // Mover en eje Z (hacia adelante)
                }
                ImGui::SameLine();
                // Botón para mover hacia atrás (Dolly out)
                if (ImGui::Button("Atrás")) {
                    camera->Dolly(0, _DOLLY_SENSITIVITY_ * -1); // Mover en eje Z (hacia atrás)
                }

                // Botón para mover hacia la derecha (Strafe right)
                if (ImGui::Button("Derecha")) {
                    camera->Dolly(_DOLLY_SENSITIVITY_, 0); // Mover en eje X (hacia la derecha)
                }
                ImGui::SameLine();
                // Botón para mover hacia la izquierda (Strafe left)
                if (ImGui::Button("Izquierda")) {
                    camera->Dolly(_DOLLY_SENSITIVITY_ * -1, 0); // Mover en eje X (hacia la izquierda)
                }
            }

            if(current_item=="Pan"){
                if(ImGui::Button("Derecha")){
                    camera->Pan(_TILT_PAN_SENSITIVITY_);
                }
                ImGui::SameLine();
                if(ImGui::Button("Izquierda")){
                    camera->Pan(_TILT_PAN_SENSITIVITY_ * -1);
                }
            }
            if (current_item == "Orbit") {
                // Botón para orbitar hacia la derecha
                if (ImGui::Button("Derecha")) {
                    camera->Orbit(_ORBIT_SENSITIVITY_, 0); // Rotar alrededor del eje Y (horizontal)
                }
                ImGui::SameLine();
                // Botón para orbitar hacia la izquierda
                if (ImGui::Button("Izquierda")) {
                    camera->Orbit(_ORBIT_SENSITIVITY_ * -1, 0); // Rotar en sentido contrario alrededor del eje Y
                }

                // Botón para orbitar hacia arriba
                if (ImGui::Button("Arriba")) {
                    camera->Orbit(0, _ORBIT_SENSITIVITY_ * -1); // Rotar alrededor del eje X (vertical)
                }
                ImGui::SameLine();
                // Botón para orbitar hacia abajo
                if (ImGui::Button("Abajo")) {
                    camera->Orbit(0, _ORBIT_SENSITIVITY_); // Rotar hacia abajo alrededor del eje X
                }
            }
            if (current_item=="Reset") {
                if(ImGui::Button("Reset")){
                    camera->ResetCamera();
                }
            }

        }
        ImGui::End();
    }

    void SelectorMovimiento::setCamera(Camera *camara){
       camera=camara;
    }

} // PAG