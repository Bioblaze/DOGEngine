#ifndef PORTAL2D_RENDERER_H
#define PORTAL2D_RENDERER_H

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

        void DrawWall(const Portal2D::Wall &wall, float x0, float y0, float x1, float y1, float wall_l, float wall_r);
        void DrawRoom(const Portal2D::Room &room, const Portal2D::Camera &camera, float clip_l, float clip_r);

        SDL_Window *GetSDLWindow();
        SDL_Renderer *GetSDLRenderer();

        std::pair<int, int> GetScreenSize();

    private:
        SDL_Window *sdl_window;
        SDL_Renderer *sdl_renderer;

        std::vector<SDL_Texture *> sdl_textures;

        int screen_width;
        int screen_height;
    };
};

#endif // PORTAL2D_RENDERER_H
