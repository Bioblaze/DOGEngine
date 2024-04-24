// DOGEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define SDL_MAIN_HANDLED
#include <iostream>
#include <map>

#include "Core/Logger.h" 
#include "Editor/BuildSystem.h"
#include "Portal2D/Renderer.h"
#include "Portal2D/Camera.h"
#include "Portal2D/Room.h"
#include "Portal2D/Wall.h"
#include "imgui.h"

int main(int argc, char* args[])
{
    Logger& appLogger = Logger::Get();
    appLogger.SetConfig("defaultLog.log", true);

    appLogger.Log("Hello World!");  // Log a simple message

    std::string timeString = appLogger.GetTimestamp();

    // Log with current time using DebugLog
    appLogger.DebugLog("Hello with fmt! Current time: {}", timeString.c_str());

    Portal2D::Room my_room_1, my_room_2;

    my_room_1.walls.push_back({&my_room_1, NULL, -3, 4, 0, 1.0f});
    my_room_1.walls.push_back({&my_room_1, &my_room_2, 4, 2, 0, 1.0f});
    my_room_1.walls.push_back({&my_room_1, NULL, 5, -2, 0, 1.0f});
    my_room_1.walls.push_back({&my_room_1, NULL, -1, -4, 0, 1.0f});
    my_room_1.walls.push_back({&my_room_1, NULL, -5, 1, 0, 1.0f});

    my_room_2.walls.push_back({&my_room_2, &my_room_1, 5, -2, 0, 4.0f});
    my_room_2.walls.push_back({&my_room_2, NULL, 4, 2, 0, 4.0f});
    my_room_2.walls.push_back({&my_room_2, NULL, 4, 6, 0, 4.0f});
    my_room_2.walls.push_back({&my_room_2, NULL, 12, 6, 0, 4.0f});
    my_room_2.walls.push_back({&my_room_2, NULL, 12, -6, 0, 4.0f});
    my_room_2.walls.push_back({&my_room_2, NULL, 4, -6, 0, 4.0f});

    Portal2D::Camera my_camera = {&my_room_1, 0.0f, 0.0f, 0.5f, 0.0f, 0.0f, 0.0f};

    try {
        Portal2D::Renderer renderer("Hello World", 800, 600);
        bool running = true;
        SDL_Event event;

        SDL_Texture *test_sdl_texture = SDL_CreateTexture(renderer.GetSDLRenderer(), SDL_PIXELFORMAT_RGB332, SDL_TEXTUREACCESS_STATIC, 1024, 1024);
        uint8_t test_pixels[1048576];

        for (int i = 0; i < 1024; i++) {
            for (int j = 0; j < 1024; j++) {
                test_pixels[j + i * 1024] = (i ^ j) ^ ((i ^ j) >> 8);
            }
        }

        SDL_UpdateTexture(test_sdl_texture, NULL, test_pixels, 1024);
        renderer.PushTexture(0, test_sdl_texture);

        std::map<int, bool> sdl_keys;

        while (running) {
            while (SDL_PollEvent(&event) != 0) {
                if (event.type == SDL_QUIT) {
                    running = false;
                } else if (event.type == SDL_KEYDOWN) {
                    sdl_keys[event.key.keysym.sym] = true;
                } else if (event.type == SDL_KEYUP) {
                    sdl_keys[event.key.keysym.sym] = false;
                }
            }


            renderer.BeginFrame(); // Prepare renderer for drawing 2D content

            renderer.DrawRoom(*(my_camera.room), my_camera, -1.0f, 1.0f); // Render the 3D view

            renderer.EndFrame();

            if (sdl_keys[SDLK_w] || sdl_keys[SDLK_UP]) {
                my_camera.point_x += sinf(my_camera.angle) * 0.1;
                my_camera.point_y += cosf(my_camera.angle) * 0.1;
            }

            if (sdl_keys[SDLK_a] || sdl_keys[SDLK_LEFT]) {
                my_camera.angle -= 0.05;
            }

            if (sdl_keys[SDLK_d] || sdl_keys[SDLK_RIGHT]) {
                my_camera.angle += 0.05;
            }

            my_camera.Update();

            // Clear screen with a color
            //SDL_SetRenderDrawColor(renderer.GetRenderer(), 0xFF, 0xFF, 0xFF, 0xFF); // White
            //SDL_RenderClear(renderer.GetRenderer());

            // Game loop content here, drawing operations...

            // Update screen
            //SDL_RenderPresent(renderer.GetRenderer());
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Exception occurred: " << e.what() << std::endl;
    }

    appLogger.Log("Press Enter to close the application...");
    std::cin.get();  // Wait for the user to press Enter

    return 0;
}
//std::string buildToolPath = "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\MSBuild\\Current\\Bin\\MSBuild.exe";
//BuildSystem buildSystem(buildToolPath);
//std::string projectPath = "E:\\DivineGames\\DungeonEngine\\DOGEngine\\DOGEngine.sln";
//std::string additionalArguments = "/p:Configuration=Debug /p:Platform=x64";

//if (buildSystem.compile(projectPath, additionalArguments, true, true)) {
//    std::cout << "Build succeeded." << std::endl;
//}
//else {
//    std::cout << "Build failed." << std::endl;
//}