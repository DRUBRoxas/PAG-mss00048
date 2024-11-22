//
// Created by Manuel on 21/11/2024.
//

#ifndef VISUALIZACION_H
#define VISUALIZACION_H
#include <string>

namespace PAG {
    enum TipoVisualizacion : int {
        ALAMBRE = 0,
        RELLENO = 1
    };
    inline std::string to_string(TipoVisualizacion tipo) {
        switch (tipo) {
            case ALAMBRE:
                return "Alambre";
            case RELLENO:
                return "Relleno";
        }
    }
}

#endif //VISUALIZACION_H
