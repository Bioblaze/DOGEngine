#ifndef PORTAL2D_ROOM_H
#define PORTAL2D_ROOM_H

#include <vector>

#include "Color.h"
#include "Wall.h"

namespace Portal2D {
    struct Room {
        std::vector<Wall> walls;
        
        float height_z;
        Color f_color, c_color;
    };
};

#endif // PORTAL2D_ROOM_H
