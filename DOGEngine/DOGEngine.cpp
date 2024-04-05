// DOGEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define SDL_MAIN_HANDLED
#include <iostream>
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
    appLogger.DebugLog("Hello with fmt! Current time: %s", timeString.c_str());

    Portal2D::Room my_room_1, my_room_2;

    my_room_1.walls.push_back({&my_room_1, NULL, -3, 4});
    my_room_1.walls.push_back({&my_room_1, &my_room_2, 4, 2});
    my_room_1.walls.push_back({&my_room_1, NULL, 5, -2});
    my_room_1.walls.push_back({&my_room_1, NULL, -1, -4});
    my_room_1.walls.push_back({&my_room_1, NULL, -5, 1});

    my_room_2.walls.push_back({&my_room_2, &my_room_1, 5, -2});
    my_room_2.walls.push_back({&my_room_2, NULL, 4, 2});
    my_room_2.walls.push_back({&my_room_2, NULL, 4, 6});
    my_room_2.walls.push_back({&my_room_2, NULL, 12, 6});
    my_room_2.walls.push_back({&my_room_2, NULL, 12, -6});
    my_room_2.walls.push_back({&my_room_2, NULL, 4, -6});

    Portal2D::Camera my_camera = {&my_room_1, 0.0f, 0.0f, 0.0f};

    try {
        Portal2D::Renderer renderer("Hello World", 800, 600);
        bool running = true;
        SDL_Event event;

        SDL_Texture *test_sdl_texture = SDL_CreateTexture(renderer.GetSDLRenderer(), SDL_PIXELFORMAT_RGB332, SDL_TEXTUREACCESS_STATIC, 256, 256);
        uint8_t test_pixels[65536];

        for (int i = 0; i < 256; i++) {
            for (int j = 0; j < 256; j++) {
                test_pixels[j + i * 256] = i ^ j;
            }
        }

        SDL_UpdateTexture(test_sdl_texture, NULL, test_pixels, 256);
        renderer.PushTexture(0, test_sdl_texture);

        while (running) {
            while (SDL_PollEvent(&event) != 0) {
                // User requests quit
                if (event.type == SDL_QUIT) {
                    running = false;
                }
            }


            renderer.BeginFrame(); // Prepare renderer for drawing 2D content

            renderer.DrawRoom(*(my_camera.room), my_camera, -1.0f, 1.0f); // Render the 3D view
            my_camera.angle += 0.01f;

            renderer.EndFrame();

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