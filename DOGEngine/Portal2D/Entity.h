#ifndef PORTAL2D_ENTITY_H
#define PORTAL2D_ENTITY_H

#include "Room.h"

namespace Portal2D {
    struct Entity {
        Room *room;

        float radius, height_z, view_z;
        int texture_id;

        float point_x, point_y, point_z;
        float angle;

        float old_point_x, old_point_y;

        void Update();
    };
};

#endif // PORTAL2D_ENTITY_H
