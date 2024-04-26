#ifndef PORTAL2D_WALL_H
#define PORTAL2D_WALL_H

#include "Room.h"

namespace Portal2D {
    struct Room;

    struct Wall {
        Room *room, *link;
        int point_x, point_y;
        
        int texture_id;
    };
};

#endif // PORTAL2D_WALL_H
