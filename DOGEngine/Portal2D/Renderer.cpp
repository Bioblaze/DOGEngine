#include <cassert>

#include "Renderer.h"

Portal2D::Renderer::Renderer(const char *title, int width, int height) {
    assert(SDL_Init(SDL_INIT_VIDEO) >= 0);
    
    this->sdl_window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    assert(this->sdl_window != nullptr);
    
    this->sdl_renderer = SDL_CreateRenderer(this->sdl_window, -1, SDL_RENDERER_ACCELERATED);
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

void Portal2D::Renderer::DrawRoom(const Portal2D::Room &room, Portal2D::Camera camera, int clip_x0, int clip_x1) {
    for (const Portal2D::Wall &wall : room.walls) {
        // TODO: Find viewing range of wall, and clip it to
        // [clip_x0, clip_x1). For now, we will assume the
        // range to be [0, this->screen_width].
        
        int wall_x0 = 0;
        int wall_x1 = this->screen_width;
        
        wall_x0 = std::max(wall_x0, clip_x0);
        wall_x1 = std::min(wall_x1, clip_x1);
        
        if (wall_x0 >= wall_x1) {
            continue;
        }
        
        if (wall.link != nullptr) {
            this->DrawRoom(*(wall.link->room), camera, wall_x0, wall_x1);
        }
    }
}

void Portal2D::Renderer::DrawScreen() {
    // TODO: Find the room the camera is in right now.
    
    /*
    Camera camera = ...;
    
    Room &room = ...;
    this->DrawRoom(room, 0, this->screen_width);
    */
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
