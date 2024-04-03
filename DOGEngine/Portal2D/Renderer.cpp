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

void Portal2D::Renderer::DrawWall(const Portal2D::Wall &wall, int screen_x0, int screen_x1, float y0, float y1) {
    // TODO: Texture mapping goes here, for now let's just be happy with having
    // some walls rendered :D.
    
    float height_y0 = 320.0f / y0;
    float height_y1 = 320.0f / y1;
    
    float quad_x0 = screen_x0;
    float quad_y0 = this->screen_height * 0.5f - height_y0;
    
    float quad_x1 = screen_x1;
    float quad_y1 = this->screen_height * 0.5f - height_y1;
    
    float quad_x2 = screen_x1;
    float quad_y2 = this->screen_height * 0.5f + height_y1;
    
    float quad_x3 = screen_x0;
    float quad_y3 = this->screen_height * 0.5f + height_y0;
    
    const SDL_Vertex sdl_array[] = {
        {(SDL_FPoint) {quad_x0, quad_y0}, (SDL_Color) {255, 0, 0, 255}, (SDL_FPoint) {0.0f, 0.0f}},
        {(SDL_FPoint) {quad_x1, quad_y1}, (SDL_Color) {0, 255, 0, 255}, (SDL_FPoint) {0.0f, 0.0f}},
        {(SDL_FPoint) {quad_x2, quad_y2}, (SDL_Color) {0, 0, 255, 255}, (SDL_FPoint) {0.0f, 0.0f}},
        {(SDL_FPoint) {quad_x3, quad_y3}, (SDL_Color) {255, 255, 0, 255}, (SDL_FPoint) {0.0f, 0.0f}},
        {(SDL_FPoint) {quad_x0, quad_y0}, (SDL_Color) {255, 0, 0, 255}, (SDL_FPoint) {0.0f, 0.0f}},
    };
    
    SDL_RenderGeometry(this->sdl_renderer, nullptr, sdl_array + 0, 3, nullptr, 0);
    SDL_RenderGeometry(this->sdl_renderer, nullptr, sdl_array + 2, 3, nullptr, 0);
}

void Portal2D::Renderer::DrawRoom(const Portal2D::Room &room, const Portal2D::Camera &camera, float clip_l, float clip_r) {
    float cos_angle = cosf(camera.angle);
    float sin_angle = sinf(camera.angle);
    
    for (auto i = 0; i < room.walls.size(); i++) {
        const Portal2D::Wall &wall = room.walls[i];
        auto j = (i + 1) % room.walls.size();
        
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
        
        if (clip_l * y0_r > x0_r) {
            double lambda = (clip_l * y0_r - x0_r) / ((x1_r - x0_r) - clip_l * (y1_r - y0_r));
            
            y0_r += (y1_r - y0_r) * lambda;
            x0_r += (x1_r - x0_r) * lambda;
        }
        
        if (clip_r * y1_r < x1_r) {
            double lambda = (clip_r * y0_r - x0_r) / ((x1_r - x0_r) - clip_r * (y1_r - y0_r));
            
            y1_r = y0_r + (y1_r - y0_r) * lambda;
            x1_r = x0_r + (x1_r - x0_r) * lambda;
        }
        
        if (y0_r < 0.0f || y1_r < 0.0f) {
            continue;
        }
        
        // wall_x0 - wall_x1 defines its linear projection.
        
        float wall_x0 = x0_r / y0_r;
        float wall_x1 = x1_r / y1_r;
        
        if (wall_x0 >= wall_x1) {
            continue;
        }
        
        // screen_x0 - screen_x1 defines the final pixel-based coordinates.
        
        int screen_x0 = (int)((wall_x0 + 1.0f) * this->screen_width * 0.5f);
        int screen_x1 = (int)((wall_x1 + 1.0f) * this->screen_width * 0.5f);
        
        // Everything before this point was just the math necessary to get it
        // working, the code below does the actual rendering with SDL2.
        
        if (wall.link == nullptr) {
            this->DrawWall(wall, screen_x0, screen_x1, y0_r, y1_r);
        } else {
            this->DrawRoom(*(wall.link), camera, wall_x0, wall_x1);
        }
    }
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
