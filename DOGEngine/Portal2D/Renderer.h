#ifndef PORTAL2D_RENDERER_H
#define PORTAL2D_RENDERER_H

#include <SDL2/SDL.h>

#include "Room.h"

namespace Portal2D {
    class Renderer {
    public:
        Renderer(const char *title, int width, int height);
        virtual ~Renderer();

        void BeginFrame();
        void EndFrame();

        void DrawRoom(const Portal2D::Room &room, int clip_x0, int clip_x1);
        void DrawScreen();

        SDL_Window *GetSDLWindow();
        SDL_Renderer *GetSDLRenderer();

        std::pair<int, int> GetScreenSize();

    private:
        SDL_Window *sdl_window;
        SDL_Renderer *sdl_renderer;

        int screen_width;
        int screen_height;
    };
};

#endif // PORTAL2D_RENDERER_H
