#include <cmath>

#include "Camera.h"
#include "Room.h"

#include <cstdio>

void Portal2D::Camera::Update() {
    const float radius = 0.125f;
    
    const float x2 = this->old_point_x;
    const float y2 = this->old_point_y;
    
    float x3 = this->point_x;
    float y3 = this->point_y;
    
    for (auto i = 0; i < this->room->walls.size(); i++) {
        const Portal2D::Wall &wall = this->room->walls[i];
        auto j = (i + 1) % this->room->walls.size();
        
        // (x0, y0) - (x1, y1) defines the wall as it exists.
        
        const float x0 = wall.point_x;
        const float y0 = wall.point_y;
        
        const float x1 = this->room->walls[j].point_x;
        const float y1 = this->room->walls[j].point_y;
        
        // A and B are scalars that indicate where in the lines
        // intersections occurred.
        
        const float d = (x0 - x1) * (y2 - y3) - (y0 - y1) * (x2 - x3);
        
        if (d == 0.0f) {
            continue;
        }
        
        const float a = ((x0 - x2) * (y2 - y3) - (y0 - y2) * (x2 - x3)) / d;
        const float b = ((x0 - x2) * (y0 - y1) - (y0 - y2) * (x0 - x1)) / d;
        
        // Discard interaction if we collided just with the wall
        // line, and not with the actual segment.
        
        if (a < 0.0f || a > 1.0f) {
            continue;
        }
        
        // Now, let the magic begin!
        
        if (wall.link == nullptr) {
            // We want the normal, so we invert the components and negate
            // one of them.
            
            const float n_length = sqrtf((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0));
            const float d_length = sqrtf((x3 - x2) * (x3 - x2) + (y3 - y2) * (y3 - y2));
            
            const float nx = (y1 - y0) / n_length;
            const float ny = (x0 - x1) / n_length;
            
            const float dx = (x3 - x2) / d_length;
            const float dy = (y3 - y2) / d_length;
            
            if (n_length == 0.0f || d_length == 0.0f) {
                continue;
            }
            
            const float cos_angle = nx * dx + ny * dy;
            
            if (cos_angle == 0.0f) {
                continue;
            }
            
            const float d_radius = radius / cos_angle;
            const float b_radius = d_radius / d_length;
            
            const float b_final = b - b_radius;
            
            if (b < 0.0f || b > 1.0f) {
                continue;
            }
            
            x3 = x2 + (x3 - x2) * b_final;
            y3 = y2 + (y3 - y2) * b_final;
        } else {
            if (b < 0.0f || b > 1.0f) {
                continue;
            }
            
            this->room = wall.link;
            break;
        }
    }
    
    this->old_point_x = this->point_x = x3;
    this->old_point_y = this->point_y = y3;
}
