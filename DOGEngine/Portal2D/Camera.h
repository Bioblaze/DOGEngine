#ifndef PORTAL2D_CAMERA_H
#define PORTAL2D_CAMERA_H

#include "Room.h"

namespace Portal2D {
    struct Camera {
        Room *room;

        float point_x, point_y, point_z;
        float angle;

        float old_point_x, old_point_y;

        void Update();
    };
};

#endif // PORTAL2D_CAMERA_H
