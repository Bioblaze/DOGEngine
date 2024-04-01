#ifndef PORTAL2D_WALL_H
#define PORTAL2D_WALL_H

#include "Room.h"

namespace Portal2D {
    struct Room;

    struct Wall {
        Room *room;
        int point_x, point_y;

        Wall *link;
    };
};

#endif // PORTAL2D_WALL_H
