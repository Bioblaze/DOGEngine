#include "Renderer.h"
#include <mutex>
#include <stdexcept>
#include <vector>
#include <cmath>


Renderer& Renderer::getInstance() {
    static std::mutex mutex;
    std::lock_guard<std::mutex> lock(mutex); // Lock for thread safety
    static Renderer instance; // C++11 magic statics for thread-safe initialization
    return instance;
}
Renderer::Renderer() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw std::runtime_error("SDL could not initialize!");
    }
}

Renderer::~Renderer() {
    if (renderer) {
        SDL_DestroyRenderer(renderer);
    }
    if (window) {
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
}

void Renderer::CreateWindow(const char* title, int width, int height) {
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (!window) {
        throw std::runtime_error("Window could not be created!");
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        throw std::runtime_error("Renderer could not be created!");
    }

    screenWidth = width;
    screenHeight = height;
}

SDL_Window* Renderer::GetWindow() const {
    return window;
}

SDL_Renderer* Renderer::GetRenderer() const {
    return renderer;
}

void Renderer::Prepare2DRender() {
    // Set draw color for clearing the screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE); // Black
    // Clear the screen
    SDL_RenderClear(renderer);

    // Now ready for drawing
    // Use SDL drawing functions like SDL_RenderCopy for textures or SDL_RenderDrawLine for lines

    // Remember to call SDL_RenderPresent(renderer); after all draw calls are done
}

void Renderer::Render3DView() {
    float rayAngle = player.angle - (player.fov / 2); // Starting angle
    float rayStep = player.fov / screenWidth; // Angle step between each vertical strip

    for (int x = 0; x < screenWidth; x++) {
        // Calculate ray direction
        float rayDirX = std::sin(rayAngle);
        float rayDirY = std::cos(rayAngle);

        // Which box of the map we're in
        int mapX = int(player.x);
        int mapY = int(player.y);

        // Length of ray from one x or y-side to next x or y-side
        float sideDistX;
        float sideDistY;

        // Length of ray from current position to next x or y-side
        float deltaDistX = (rayDirX == 0) ? 1e30 : std::abs(1 / rayDirX);
        float deltaDistY = (rayDirY == 0) ? 1e30 : std::abs(1 / rayDirY);
        float perpWallDist;

        //what direction to step in x or y-direction (either +1 or -1)
        int stepX, stepY;

        bool hit = false; // was a wall hit?
        int side; // was a NS or a EW wall hit?

        // calculate step and initial sideDist
        if (rayDirX < 0) {
            stepX = -1;
            sideDistX = (player.x - mapX) * deltaDistX;
        }
        else {
            stepX = 1;
            sideDistX = (mapX + 1.0 - player.x) * deltaDistX;
        }
        if (rayDirY < 0) {
            stepY = -1;
            sideDistY = (player.y - mapY) * deltaDistY;
        }
        else {
            stepY = 1;
            sideDistY = (mapY + 1.0 - player.y) * deltaDistY;
        }

        // Perform DDA
        while (!hit) {
            // jump to next map square, in x-direction or in y-direction
            if (sideDistX < sideDistY) {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            }
            else {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
            // Check if ray has hit a wall
            if (map[mapY][mapX] > 0) hit = true;
        }

        // Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
        if (side == 0) perpWallDist = (mapX - player.x + (1 - stepX) / 2) / rayDirX;
        else perpWallDist = (mapY - player.y + (1 - stepY) / 2) / rayDirY;

        // Calculate the height of the wall based on the distance from the camera
        int lineHeight = (int)(screenHeight / perpWallDist);

        // calculate lowest and highest pixel to fill in current stripe
        int drawStart = -lineHeight / 2 + screenHeight / 2;
        if (drawStart < 0) drawStart = 0;
        int drawEnd = lineHeight / 2 + screenHeight / 2;
        if (drawEnd >= screenHeight) drawEnd = screenHeight - 1;

        // Render the wall stripe
        for (int y = 0; y < screenHeight; y++) {
            if (y < drawStart) SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Sky
            else if (y > drawEnd) SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Floor
            else SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Wall

            SDL_RenderDrawPoint(renderer, x, y);
        }

        rayAngle += rayStep; // Move to the next ray
    }

    SDL_RenderPresent(renderer); // Present the frame
}
