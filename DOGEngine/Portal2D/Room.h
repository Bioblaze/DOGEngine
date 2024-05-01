#ifndef PORTAL2D_ROOM_H
#define PORTAL2D_ROOM_H

#include <vector>
#include <set>

#include "Color.h"
#include "Wall.h"

namespace Portal2D {
    struct Entity;
    
    struct Room {
        std::vector<Wall> walls;
        std::set<Entity *> entities;
        
        float height_z;
        Color f_color, c_color;
    };
};

#endif // PORTAL2D_ROOM_H
