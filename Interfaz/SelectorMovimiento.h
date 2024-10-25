//
// Created by Manuel on 22/10/2024.
//

#ifndef SELECTORMOVIMIENTO_H
#define SELECTORMOVIMIENTO_H

#include "imgui/imgui.h"
#include "../Camera.h"
namespace PAG {

class SelectorMovimiento {
private:
    Camera *camera;
public:
    float zoom=0.0f;
    float crane=0.0f;
    float tilt=0.0f;
    float dolly=0.0f;
    float pan=0.0f;
    float orbit=0.0f;

    void setCamera(Camera *camara);
    SelectorMovimiento();
    ~SelectorMovimiento();
   void RefrescarSelector();

};

} // PAG

#endif //SELECTORMOVIMIENTO_H
