#include <cmath>

#include "Camera.h"
#include "Room.h"

#include <cstdio>

void Portal2D::Camera::Update() {
    // TODO: check if camera got outside its room and update
    // this->room accordingly.
    
    const float radius = 0.125f;
    
    float cx = this->old_point_x;
    float cy = this->old_point_y;
    
    float delta_cx = this->point_x - cx;
    float delta_cy = this->point_y - cy;
    
    float cd = sqrtf(delta_cx * delta_cx + delta_cy * delta_cy);
    
    if (cd == 0.0f) {
        return;
    }
    
    delta_cx /= cd;
    delta_cy /= cd;
    
    while (cd > 0.0f) {
        float step = std::min(cd, radius * 0.0625f);
        cd -= step;
        
        cx += delta_cx * step;
        cy += delta_cy * step;
        
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
            
            float a = (x0 * x0 + y0 * y0 + x1 * cx + y1 * cy - x0 * (x1 + cx) - y0 * (y1 + cy));
            float b = (x0 - x1) * (x0 - x1) + (y0 - y1) * (y0 - y1);
            
            if (b == 0.0f) {
                continue;
            }
            
            float k = std::max(std::min(a / b, 1.0f), 0.0f);
            
            float px = x0 + (x1 - x0) * k;
            float py = y0 + (y1 - y0) * k;
            
            float nx = cx - px;
            float ny = cy - py;
            
            float d = sqrtf(nx * nx + ny * ny);
            
            nx /= d;
            ny /= d;
            
            if (wall.link == nullptr) {
                if (d < radius) {
                    cx += nx * (radius - d);
                    cy += ny * (radius - d);
                }
            } else {
                if (d < 0.0f) {
                    // this->room = wall.link;
                    // break;
                }
            }
        }
        
    }
    
    this->point_x = this->old_point_x = cx;
    this->point_y = this->old_point_y = cy;
}
