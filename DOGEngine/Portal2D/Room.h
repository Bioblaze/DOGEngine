#ifndef PORTAL2D_ROOM_H
#define PORTAL2D_ROOM_H

#include <vector>

#include "Wall.h"

namespace Portal2D {
    struct Room {
        std::vector<Wall> walls;
    };
};

#endif // PORTAL2D_ROOM_H
