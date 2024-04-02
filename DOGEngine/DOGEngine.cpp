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

    Portal2D::Room my_room;

    my_room.walls.push_back({&my_room, -3, 4, NULL});
    my_room.walls.push_back({&my_room, 4, 2, NULL});
    my_room.walls.push_back({&my_room, 5, -2, NULL});
    my_room.walls.push_back({&my_room, -1, -4, NULL});
    my_room.walls.push_back({&my_room, -5, 1, NULL});

    Portal2D::Camera my_camera = {0.0f, 0.0f, 0.0f};

    try {
        Portal2D::Renderer renderer("Hello World", 800, 600);
        bool running = true;
        SDL_Event event;

        while (running) {
            while (SDL_PollEvent(&event) != 0) {
                // User requests quit
                if (event.type == SDL_QUIT) {
                    running = false;
                }
            }


            renderer.BeginFrame(); // Prepare renderer for drawing 2D content

            renderer.DrawRoom(my_room, my_camera, 0, 800); // Render the 3D view
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