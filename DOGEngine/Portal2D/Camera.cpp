#include <cmath>

#include "Camera.h"
#include "Room.h"

#include <cstdio>

void Portal2D::Camera::Update() {
    // TODO: check if camera got outside its room and update
    // this->room accordingly.
    
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
            const float cos_d = sqrtf(((x0 - x1) * (x0 - x1) + (y0 - y1) * (y0 - y1)) * ((x2 - x3) * (x2 - x3) + (y2 - y3) * (y2 - y3)));
            
            if (cos_d == 0.0f) {
                continue;
            }
            
            const float cos_x = fabsf(d) / cos_d;
            
            const float b_delta = (radius / cos_x) / sqrtf((x0 - x1) * (x0 - x1) + (y0 - y1) * (y0 - y1));
            const float b_final = b - 0.0f * b_delta;
            
            if (b_final > 0.0f && b_final < 1.0f) {
                x3 = x2 + (x3 - x2) * b_final * 0.5f;
                y3 = y2 + (y3 - y2) * b_final * 0.5f;
            }
        } else {
            if (b < 0.0f || b > 1.0f) {
                continue;
            }
            
            this->room = wall.link;
            break;
        }
    }
    
    /*
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
    */
    
    this->old_point_x = this->point_x = x3;
    this->old_point_y = this->point_y = y3;
}
