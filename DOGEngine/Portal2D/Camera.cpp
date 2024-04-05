#include <cmath>

#include "Camera.h"
#include "Room.h"

#include <cstdio>

void Portal2D::Camera::Update() {
    // TODO: check if camera got outside its room and update
    // this->room accordingly.
    
    for (auto i = 0; i < this->room->walls.size(); i++) {
        const Portal2D::Wall &wall = this->room->walls[i];
        auto j = (i + 1) % this->room->walls.size();
        
        // (x0, y0) - (x1, y1) defines the wall as it exists.
        
        float x0 = wall.point_x;
        float y0 = wall.point_y;
        
        float x1 = this->room->walls[j].point_x;
        float y1 = this->room->walls[j].point_y;
        
        // Calculate the distance from the camera to the wall, to check
        // for possible collisions.
        
        float nx = y1 - y0;
        float ny = x0 - x1;
        
        float a = (x1 - x0) * (y0 - this->point_y) - (y1 - y0) * (x0 - this->point_x);
        float b = sqrtf((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0));
        
        nx /= b;
        ny /= b;
        
        float d = a / b;
        // printf("%f\n", d);
        
        if (wall.link == nullptr) {
            if (d < 0.125f) {
                this->point_x += nx * (0.125f - d);
                this->point_y += ny * (0.125f - d);
            }
        } else {
            if (d < 0.0f) {
                this->room = wall.link;
                break;
            }
        }
    }
}
