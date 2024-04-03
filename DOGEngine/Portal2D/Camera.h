#ifndef PORTAL2D_CAMERA_H
#define PORTAL2D_CAMERA_H

#include "Room.h"

namespace Portal2D {
    struct Camera {
        Room *room;
        
        float point_x, point_y;
        float angle;

        void update();
    };
};

#endif // PORTAL2D_CAMERA_H
