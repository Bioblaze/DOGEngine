#include <cmath>

#include "Entity.h"
#include "Room.h"

void Portal2D::Entity::Update() {
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
        
        // (nx, ny) defines the inner normal of the wall.
        
        const float wall_length = sqrtf((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0));
        
        const float nx = (y1 - y0) / wall_length;
        const float ny = (x0 - x1) / wall_length;
        
        // (px0, py0) - (px1, py1) defines the wall with the
        // camera this->radius compensation added in.
        
        const float px0 = x0 + nx * this->radius;
        const float py0 = y0 + ny * this->radius;
        
        const float px1 = x1 + nx * this->radius;
        const float py1 = y1 + ny * this->radius;
        
        // A and B are scalars that indicate where in the lines
        // intersections occurred.
        
        const float d = (px0 - px1) * (y2 - y3) - (py0 - py1) * (x2 - x3);
        
        if (d == 0.0f) {
            continue;
        }
        
        const float a = ((px0 - x2) * (y2 - y3) - (py0 - y2) * (x2 - x3)) / d;
        const float b = ((px0 - x2) * (py0 - py1) - (py0 - y2) * (px0 - px1)) / d;
        
        // Discard interaction if we just did not collide.
        
        if (b < 0.0f || b > 1.0f) {
            continue;
        }
        
        // Treat line-line and line-circle collisions separately
        // from now on.
        
        if (a < 0.0f) {
            const float t0 = x2 * x2 - x0 * x2 - x2 * x3 + x0 * x3 + y2 * y2 - y0 * y2 - y2 * y3 + y0 * y3;
            const float t1 = 2.0f * (x2 * x3 + y2 * y3) - x2 * x2 - x3 * x3 - y2 * y2 - y3 * y3;
            const float t2 = 2.0f * (x0 * x2 + y0 * y2) + this->radius * this->radius - x0 * x0 - x2 * x2 - y0 * y0 - y2 * y2;
            
            if (t1 == 0.0f || t0 * t0 < t1 * t2) {
                continue;
            }
            
            const float c = (sqrtf(t0 * t0 - t1 * t2) - t0) / t1;
            
            if (c < 0.0f || c > 1.0f) {
                continue;
            }
            
            if (wall.link == nullptr) {
                x3 = x2 + (x3 - x2) * (c - 0.001f);
                y3 = y2 + (y3 - y2) * (c - 0.001f);
            } else {
                this->point_z = std::min(this->point_z, wall.link->height_z - this->height_z);
            }
        } else if (a > 1.0f) {
            const float t0 = x2 * x2 - x1 * x2 - x2 * x3 + x1 * x3 + y2 * y2 - y1 * y2 - y2 * y3 + y1 * y3;
            const float t1 = 2.0f * (x2 * x3 + y2 * y3) - x2 * x2 - x3 * x3 - y2 * y2 - y3 * y3;
            const float t2 = 2.0f * (x1 * x2 + y1 * y2) + this->radius * this->radius - x1 * x1 - x2 * x2 - y1 * y1 - y2 * y2;
            
            if (t1 == 0.0f || t0 * t0 < t1 * t2) {
                continue;
            }
            
            const float c = (sqrtf(t0 * t0 - t1 * t2) - t0) / t1;
            
            if (c < 0.0f || c > 1.0f) {
                continue;
            }
            
            if (wall.link == nullptr) {
                x3 = x2 + (x3 - x2) * (c - 0.001f);
                y3 = y2 + (y3 - y2) * (c - 0.001f);
            } else {
                this->point_z = std::min(this->point_z, wall.link->height_z - this->height_z);
            }
        } else {
            const float dot = nx * (x2 - x3) + ny * (y2 - y3);
            const float p = (1.0f - b) * dot;
            
            if (wall.link == nullptr) {
                x3 = x3 + nx * (p + 0.001f);
                y3 = y3 + ny * (p + 0.001f);
            } else {
                this->point_z = std::min(this->point_z, wall.link->height_z - this->height_z);
            }
        }
    }
    
    for (auto i = 0; i < this->room->walls.size(); i++) {
        const Portal2D::Wall &wall = this->room->walls[i];
        auto j = (i + 1) % this->room->walls.size();
        
        if (wall.link == nullptr) {
            continue;
        }
        
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
        // line, and not with the actual segment, or if we just
        // did not collide.
        
        if (a < 0.0f || a > 1.0f) {
            continue;
        }
        
        if (b < 0.0f || b > 1.0f) {
            continue;
        }
        
        // Switch to the new room we are in!
        
        this->room = wall.link;
        break;
    }
    
    this->old_point_x = this->point_x = x3;
    this->old_point_y = this->point_y = y3;
    
    this->point_z = std::min(this->point_z, this->room->height_z - this->height_z);
    this->point_z = std::max(this->point_z, 0.0f);
}
