#include <algorithm>
#include <cassert>
#include <cmath>

#include "Renderer.h"

Portal2D::Renderer::Renderer(const char *title, int width, int height) {
    assert(SDL_Init(SDL_INIT_VIDEO) >= 0);
    
    this->sdl_window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    assert(this->sdl_window != nullptr);
    
    this->sdl_renderer = SDL_CreateRenderer(this->sdl_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    assert(this->sdl_renderer != nullptr);
    
    this->screen_width = width;
    this->screen_height = height;
}

Portal2D::Renderer::~Renderer() {
    for (auto &p : this->sdl_textures) {
        SDL_DestroyTexture(p.second);
    }

    if (this->sdl_renderer) {
        SDL_DestroyRenderer(this->sdl_renderer);
    }

    if (this->sdl_window) {
        SDL_DestroyWindow(this->sdl_window);
    }

    SDL_Quit();
}

void Portal2D::Renderer::BeginFrame() {
    SDL_SetRenderDrawColor(this->sdl_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(this->sdl_renderer);
}

void Portal2D::Renderer::EndFrame() {
    SDL_RenderPresent(this->sdl_renderer);
}

void Portal2D::Renderer::DrawDecal(const Portal2D::Wall &wall, float x0, float y0, float x1, float y1, float z, float height_z, float texture_l, float texture_r, float texture_d, float shade) {
    const float scale = this->screen_height * 0.5f;
    const float halve = 8.0f;
    
    float quad_x0 = (x0 / y0 + 1.0f) * this->screen_width * 0.5f;
    float quad_y0 = scale + ((scale * (z - height_z)) / y0);
    
    float quad_x1 = (x1 / y1 + 1.0f) * this->screen_width * 0.5f;
    float quad_y1 = scale + ((scale * (z - height_z)) / y1);
    
    float quad_x2 = (x1 / y1 + 1.0f) * this->screen_width * 0.5f;
    float quad_y2 = scale + ((scale * z) / y1);
    
    float quad_x3 = (x0 / y0 + 1.0f) * this->screen_width * 0.5f;
    float quad_y3 = scale + ((scale * z) / y0);
    
    if (quad_x1 - quad_x0 > halve) {
        float xm = (x0 + x1) * 0.5f;
        float ym = (y0 + y1) * 0.5f;
        
        float texture_m = (texture_l + texture_r) * 0.5f;
        
        this->DrawDecal(wall, x0, y0, xm, ym, z, height_z, texture_l, texture_m, texture_d, shade);
        this->DrawDecal(wall, xm, ym, x1, y1, z, height_z, texture_m, texture_r, texture_d, shade);
        
        return;
    }
    
    const int v = (int)(shade * 255.0f);
    
    const SDL_Vertex sdl_array[] = {
        {(SDL_FPoint) {quad_x0, quad_y0}, (SDL_Color) {v, v, v, 255}, (SDL_FPoint) {texture_l, 1.0f}},
        {(SDL_FPoint) {quad_x1, quad_y1}, (SDL_Color) {v, v, v, 255}, (SDL_FPoint) {texture_r, 1.0f}},
        {(SDL_FPoint) {quad_x2, quad_y2}, (SDL_Color) {v, v, v, 255}, (SDL_FPoint) {texture_r, texture_d}},
        {(SDL_FPoint) {quad_x3, quad_y3}, (SDL_Color) {v, v, v, 255}, (SDL_FPoint) {texture_l, texture_d}},
        {(SDL_FPoint) {quad_x0, quad_y0}, (SDL_Color) {v, v, v, 255}, (SDL_FPoint) {texture_l, 1.0f}},
    };
    
    SDL_Texture *sdl_texture = nullptr;
    
    if (this->sdl_textures.count(wall.texture_id)) {
        sdl_texture = this->sdl_textures[wall.texture_id];
    }
    
    SDL_RenderGeometry(this->sdl_renderer, sdl_texture, sdl_array + 0, 3, nullptr, 0);
    SDL_RenderGeometry(this->sdl_renderer, sdl_texture, sdl_array + 2, 3, nullptr, 0);
}

void Portal2D::Renderer::DrawFloor(const Portal2D::Entity &camera, float x0, float y0, float x1, float y1, float z, Portal2D::Color color, bool is_floor) {
    const float scale = this->screen_height * 0.5f;
    
    float quad_x0 = (x0 / y0 + 1.0f) * this->screen_width * 0.5f;
    float quad_y0 = scale + ((scale * z) / y0);
    
    float quad_x1 = (x1 / y1 + 1.0f) * this->screen_width * 0.5f;
    float quad_y1 = scale + ((scale * z) / y1);
    
    float quad_x2 = (x1 / y1 + 1.0f) * this->screen_width * 0.5f;
    float quad_y2 = (is_floor ? (this->screen_height * 10.0f) : (-9.0f * this->screen_height));
    
    float quad_x3 = (x0 / y0 + 1.0f) * this->screen_width * 0.5f;
    float quad_y3 = (is_floor ? (this->screen_height * 10.0f) : (-9.0f * this->screen_height));
    
    const SDL_Color sdl_color = {
        (int)(std::min(std::max(color.red, 0.0f), 255.0f)),
        (int)(std::min(std::max(color.green, 0.0f), 255.0f)),
        (int)(std::min(std::max(color.blue, 0.0f), 255.0f)),
    };
    
    const SDL_Vertex sdl_array[] = {
        {(SDL_FPoint) {quad_x0, quad_y0}, sdl_color, (SDL_FPoint) {0.0f, 0.0f}},
        {(SDL_FPoint) {quad_x1, quad_y1}, sdl_color, (SDL_FPoint) {0.0f, 0.0f}},
        {(SDL_FPoint) {quad_x2, quad_y2}, sdl_color, (SDL_FPoint) {0.0f, 0.0f}},
        {(SDL_FPoint) {quad_x3, quad_y3}, sdl_color, (SDL_FPoint) {0.0f, 0.0f}},
        {(SDL_FPoint) {quad_x0, quad_y0}, sdl_color, (SDL_FPoint) {0.0f, 0.0f}},
    };
    
    SDL_RenderGeometry(this->sdl_renderer, nullptr, sdl_array + 0, 3, nullptr, 0);
    SDL_RenderGeometry(this->sdl_renderer, nullptr, sdl_array + 2, 3, nullptr, 0);
}

void Portal2D::Renderer::DrawWall(const Portal2D::Wall &wall, float x0, float y0, float x1, float y1, float z, float height_z, float wall_l, float wall_r, float wall_d, float shade) {
    float dx = x1 - x0;
    float dy = y1 - y0;
    
    float dm = sqrtf(dx * dx + dy * dy);
    
    dx /= dm;
    dy /= dm;
    
    float decal_l = dm * wall_l;
    float texture_l = fmodf(decal_l, 1.0f);
    
    while (decal_l < dm * wall_r) {
        float decal_r = (decal_l - texture_l) + 1.0f;
        float texture_r = 1.0f;
        
        if (decal_r > dm * wall_r) {
            decal_r = dm * wall_r;
            texture_r = decal_r - (decal_l - texture_l);
        }
        
        float decal_x0 = x0 + dx * decal_l;
        float decal_y0 = y0 + dy * decal_l;
        
        float decal_x1 = x0 + dx * decal_r;
        float decal_y1 = y0 + dy * decal_r;
        
        float texture_d = wall_d;
        float decal_z = 0.0f;
        
        while (decal_z < height_z) {
            float decal_h = 1.0f - texture_d;
            
            this->DrawDecal(wall, decal_x0, decal_y0, decal_x1, decal_y1, z - decal_z, decal_h, texture_l, texture_r, texture_d, shade);
            
            texture_d = 0.0f;
            decal_z += decal_h;
        }
        
        texture_l = 0.0f;
        decal_l = decal_r;
    }
}

void Portal2D::Renderer::DrawRoom(const Portal2D::Room &room, const Portal2D::Entity &camera, float clip_l, float clip_r) {
    float cos_angle = cosf(camera.angle);
    float sin_angle = sinf(camera.angle);
    
    // FIRST PASS: reorder walls using their midpoint (after clipping).
    
    std::vector<std::pair<float, int>> wall_ys(room.walls.size());
    
    // TODO: leave figuring out a structure to reuse calculated values
    // for tomorrow, I'm tired :p.
    
    for (int i = 0; i < room.walls.size(); i++) {
        const Portal2D::Wall &wall = room.walls[i];
        int j = (i + 1) % room.walls.size();
        
        // (x0, y0) - (x1, y1) defines the wall as it exists.
        
        float x0 = wall.point_x - camera.point_x;
        float y0 = wall.point_y - camera.point_y;
        
        float x1 = room.walls[j].point_x - camera.point_x;
        float y1 = room.walls[j].point_y - camera.point_y;
        
        // (x0_r, y0_r) - (x1_r, y1_r) defines the wall after its rotation.
        
        float x0_r = x0 * cos_angle - y0 * sin_angle;
        float y0_r = x0 * sin_angle + y0 * cos_angle;
        
        float x1_r = x1 * cos_angle - y1 * sin_angle;
        float y1_r = x1 * sin_angle + y1 * cos_angle;
        
        // Clip the walls to the 2D camera frustum.
        
        float wall_l = 0.0f;
        float wall_r = 1.0f;
        
        if (clip_l * y0_r > x0_r) {
            wall_l = (clip_l * y0_r - x0_r) / ((x1_r - x0_r) - clip_l * (y1_r - y0_r));
        }
        
        if (clip_r * y1_r < x1_r) {
            wall_r = (clip_r * y0_r - x0_r) / ((x1_r - x0_r) - clip_r * (y1_r - y0_r));
        }
        
        if (y0_r + (y1_r - y0_r) * wall_l < 0.0f || y0_r + (y1_r - y0_r) * wall_r < 0.0f) {
            wall_ys[i] = {0.0f, -1};
            continue;
        }
        
        float clip_x0 = x0_r + (x1_r - x0_r) * wall_l;
        float clip_y0 = y0_r + (y1_r - y0_r) * wall_l;
        
        float clip_x1 = x0_r + (x1_r - x0_r) * wall_r;
        float clip_y1 = y0_r + (y1_r - y0_r) * wall_r;
        
        wall_ys[i] = {clip_y0 + clip_y1, i};
    }
    
    std::sort(wall_ys.begin(), wall_ys.end());
    
    // SECOND PASS: actually render them.
    
    for (int _i = room.walls.size() - 1; _i >= 0; _i--) {
        const int i = wall_ys[_i].second;
        
        if (i < 0) {
            continue;
        }
        
        const Portal2D::Wall &wall = room.walls[i];
        int j = (i + 1) % room.walls.size();
        
        // (x0, y0) - (x1, y1) defines the wall as it exists.
        
        float x0 = wall.point_x - camera.point_x;
        float y0 = wall.point_y - camera.point_y;
        
        float x1 = room.walls[j].point_x - camera.point_x;
        float y1 = room.walls[j].point_y - camera.point_y;
        
        // (x0_r, y0_r) - (x1_r, y1_r) defines the wall after its rotation.
        
        float x0_r = x0 * cos_angle - y0 * sin_angle;
        float y0_r = x0 * sin_angle + y0 * cos_angle;
        
        float x1_r = x1 * cos_angle - y1 * sin_angle;
        float y1_r = x1 * sin_angle + y1 * cos_angle;
        
        // Clip the walls to the 2D camera frustum.
        
        float wall_l = 0.0f;
        float wall_r = 1.0f;
        
        if (clip_l * y0_r > x0_r) {
            wall_l = (clip_l * y0_r - x0_r) / ((x1_r - x0_r) - clip_l * (y1_r - y0_r));
        }
        
        if (clip_r * y1_r < x1_r) {
            wall_r = (clip_r * y0_r - x0_r) / ((x1_r - x0_r) - clip_r * (y1_r - y0_r));
        }
        
        if (y0_r + (y1_r - y0_r) * wall_l < 0.0f || y0_r + (y1_r - y0_r) * wall_r < 0.0f) {
            continue;
        }
        
        float clip_x0 = x0_r + (x1_r - x0_r) * wall_l;
        float clip_y0 = y0_r + (y1_r - y0_r) * wall_l;
        
        float clip_x1 = x0_r + (x1_r - x0_r) * wall_r;
        float clip_y1 = y0_r + (y1_r - y0_r) * wall_r;
        
        float view_x0 = clip_x0 / clip_y0;
        float view_x1 = clip_x1 / clip_y1;
        
        if (view_x0 >= view_x1) {
            continue;
        }
        
        // Get, using some approximations, the shade level for the wall.
        
        float tan_w = (y1 - y0) / (x1 - x0);
        float cos_w = 1.0f / (1.0f + (tan_w * tan_w) / 3.0f);
        
        float shade = (cos_w + 3.0f) * 0.25f;
        
        // Everything before this point was just the math necessary to get it
        // working, the code below does the actual rendering with SDL2.
        
        if (wall.link == nullptr) {
            this->DrawWall(wall, x0_r, y0_r, x1_r, y1_r, camera.point_z, room.height_z, wall_l, wall_r, 0.0f, shade);
        } else {
            this->DrawRoom(*(wall.link), camera, view_x0, view_x1);
            
            if (wall.link->height_z < room.height_z) {
                float wall_d = fmodf(wall.link->height_z, 1.0f);
                this->DrawWall(wall, x0_r, y0_r, x1_r, y1_r, camera.point_z - wall.link->height_z, room.height_z - wall.link->height_z, wall_l, wall_r, wall_d, shade);
            }
        }
        
        this->DrawFloor(camera, clip_x0, clip_y0, clip_x1, clip_y1, camera.point_z, room.f_color, true);
        this->DrawFloor(camera, clip_x0, clip_y0, clip_x1, clip_y1, camera.point_z - room.height_z, room.c_color, false);
    }
}

void Portal2D::Renderer::PushTexture(int id, SDL_Texture *sdl_texture) {
    this->sdl_textures[id] = sdl_texture;
}

SDL_Window *Portal2D::Renderer::GetSDLWindow() {
    return this->sdl_window;
}

SDL_Renderer *Portal2D::Renderer::GetSDLRenderer() {
    return this->sdl_renderer;
}

std::pair<int, int> Portal2D::Renderer::GetScreenSize() {
    return {this->screen_width, this->screen_height};
}
