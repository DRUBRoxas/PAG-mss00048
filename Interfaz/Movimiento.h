//
// Created by Manuel on 22/10/2024.
//

#ifndef MOVIMIENTO_H
#define MOVIMIENTO_H



//Enum para los movimientos de la cámara
enum class Movimiento : int {
    None=0,
    Zoom=1,
    Crane=2,
    Tilt=3,
    Dolly=4,
    Pan=5,
    Orbit=6
};
#endif //MOVIMIENTO_H
