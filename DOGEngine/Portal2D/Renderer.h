#ifndef PORTAL2D_RENDERER_H
#define PORTAL2D_RENDERER_H

#include <unordered_map>
#include <SDL2/SDL.h>

#include "Camera.h"
#include "Room.h"
#include "Wall.h"

namespace Portal2D {
    class Renderer {
    public:
        Renderer(const char *title, int width, int height);
        virtual ~Renderer();

        void BeginFrame();
        void EndFrame();

        void DrawDecal(const Portal2D::Wall &wall, float x0, float y0, float x1, float y1, float z, float height_z, float texture_l, float texture_r, float texture_d, float shade);
        void DrawFloor(const Portal2D::Camera &camera, float x0, float y0, float x1, float y1, float z, Portal2D::Color color, bool is_floor);

        void DrawWall(const Portal2D::Wall &wall, float x0, float y0, float x1, float y1, float z, float height_z, float wall_l, float wall_r, float wall_d, float shade);

        void DrawRoom(const Portal2D::Room &room, const Portal2D::Camera &camera, float clip_l, float clip_r);

        void PushTexture(int id, SDL_Texture *sdl_texture);

        SDL_Window *GetSDLWindow();
        SDL_Renderer *GetSDLRenderer();

        std::pair<int, int> GetScreenSize();

    private:
        SDL_Window *sdl_window;
        SDL_Renderer *sdl_renderer;

        std::unordered_map<int, SDL_Texture *> sdl_textures;

        int screen_width;
        int screen_height;
    };
};

#endif // PORTAL2D_RENDERER_H
